/*
 * callbacks.c
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.h"
#include "callbacks.h"
#include "consoleIO.h"

/* Callback functions */

void myDisplay(void)
{
	int i;
	int indexArrayVertices;
	int indexArrayNormais;
	int indexArrayCores;
	float auxP[4];
	float *pontoP = NULL;
	float auxN[4];
	float *vectorN = NULL;
	float vectorL[4];
	float *vectorV = NULL;
	float *vectorH = NULL;
	float cosNL;
	float cosNH;
	GLfloat ambientTerm[3];
	GLfloat diffuseTerm[3];
	GLfloat specularTerm[3];
	/* Limpar a janela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* SHADERS */
	glUseProgram(programaGLSL);
	/* Input para o Vertex-Shader */
	glEnableVertexAttribArray(attribute_coord3d);
	glEnableVertexAttribArray(attribute_corRGB);
	/* Caracteristicas do array de coordenadas */
	glVertexAttribPointer(attribute_coord3d,  // attribute
						  3,                 // number of elements per vertex, here (x,y,z)
						  GL_FLOAT,          // the type of each element
						  GL_FALSE,          // take our values as-is
						  0,                 // no extra data between each position
						  models.arrayVertices);    // pointer to the C array
	/* Caracteristicas do array de cores */
	glVertexAttribPointer(attribute_corRGB,  // attribute
						  3,                 // number of elements per vertex, here (R,G,B)
						  GL_FLOAT,          // the type of each element
						  GL_FALSE,          // take our values as-is
						  0,                 // no extra data between each position
						  models.arrayCores);     // pointer to the C array
	/* ATENCAO : Ordem das transformacoes !! */
	matrizModelView = IDENTITY_MATRIX;
	/* Deslocar para mais longe */
	Translate(&matrizModelView, models.desl.x, models.desl.y, models.desl.z);
	RotateAboutX(&matrizModelView, DegreesToRadians(models.anguloRot.x));
	RotateAboutY(&matrizModelView, DegreesToRadians(models.anguloRot.y));
	RotateAboutZ(&matrizModelView, DegreesToRadians(models.anguloRot.z));
	/* Diminuir o tamanho do modelo para nao sair fora do view volume */
	Scale(&matrizModelView, models.factorEsc.x, models.factorEsc.y, models.factorEsc.z);
	/* Matriz de projeccao */
	glUniformMatrix4fv(uniform_matriz_proj, 1, GL_FALSE, matrizProj.m);
	/* Matriz de transformacao */
	glUniformMatrix4fv(uniform_matriz_model_view, 1, GL_FALSE, matrizModelView.m);
	/* Phong Illumination Model */
	/* Compute the 3 components: AMBIENT, DIFFUSE and SPECULAR */
	/* INITIALIZE THE 3 COMPONENTS WITH THE CONSTANT FACTORS */
	/* AMBIENT ILLUMINATION IS CONSTANT */
	for (i = 0; i < 3; i++)
	{
		ambientTerm[i] = models.kAmb[i] * models.intensidadeLuzAmbiente[i]; /* TESTING */
		diffuseTerm[i] = models.kDif[i] * models.intensidadeFLuz_0[i];
		specularTerm[i] = models.kEsp[i] * models.intensidadeFLuz_0[i];
	}
	/* SMOOTH-SHADING */
	/* Compute the illumination RGB value for every triangle vertex */
	/* Store the RGB values in the color array */
	indexArrayCores = 0;
	GLfloat normalDifuse = 0;
	GLfloat normalSpecular = 0;
	for (indexArrayVertices = 0; indexArrayVertices < (3 * models.numVertices); indexArrayVertices += 3)
	{
		/* For every vertex */
		/* Get the XYZ coordinates and the normal vector */
		for (i = 0; i < 3; i++)
		{
			auxP[i] = models.arrayVertices[ indexArrayVertices + i ];
			auxN[i] = models.arrayNormais[ indexArrayVertices + i ];
		}
		/* The 4th homogeneous coordinate */
		auxP[3] = 1.0;
		auxN[3] = 0.0;
		/* Apply the global transformation matrix to each vertex */
		pontoP = multiplyPointByMatrix(&matrizModelView, auxP);
		/* And to the corresponding normal vector */
		vectorN = multiplyVectorByMatrix(&matrizModelView, auxN);
		/* Get the corresponding unit normal vector */
		convertToUnitVector(vectorN);
		/* DIFFUSE REFLECTION */
		/* Compute the vector L */
		for (i = 0; i < 3; i++)
		{
			vectorL[i] = models.posicaoFLuz_0[i];
		}
		/* TWO SITUATIONS : POINT light source versus DIRECTIONAL light source */
		/* Get the corresponding unit vector */
		convertToUnitVector(vectorL);
		/* Compute cos (N . L) */
		cosNL = computeScalarProduct(vectorN, vectorL);
		// STOP and CHECK if you get the expected results 
		/* SPECULAR REFLECTION */
		/* Compute the vector V --- The viewer is at (0,0,0) */
		vectorV = computeSymmetricVector(pontoP);
		/* Compute the HALFWAY VECTOR */
		vectorH = addVector(vectorL, vectorV);
		/* Get the corresponding unit vector */
		convertToUnitVector(vectorH);
		/* Compute cos (N . H) */
		cosNH = computeScalarProduct(vectorN, vectorH);
		/* STOP and CHECK if you get the expected results */
		/* ADD UP the 3 illumination components */
		/* AVOID RGB values greater the 1.0 */
		/* ONLY the AMBIENT component is being used at this moment... */
		models.arrayCores[indexArrayCores] = ambientTerm[0] + diffuseTerm[0] * cosNL + specularTerm[0] * pow(cosNH, models.coefPhong);
		indexArrayCores++;
		models.arrayCores[indexArrayCores] = ambientTerm[1] + diffuseTerm[1] * cosNL + specularTerm[1] * pow(cosNH, models.coefPhong);
		indexArrayCores++;
		models.arrayCores[indexArrayCores] = ambientTerm[2] + diffuseTerm[2] * cosNL + specularTerm[2] * pow(cosNH, models.coefPhong);
		indexArrayCores++;
		/* Libertar os arrays temporarios */
		free(pontoP);
		free(vectorN);
		free(vectorV);
		free(vectorH);
	}
	/* Push each element to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, models.numVertices);
	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_corRGB);
	/* Display the result */
	/* DOUBLE-BUFFERING */
	glutSwapBuffers();
}


void myKeyboard(unsigned char key, int x, int y)
{
	/* Usar as teclas Q ou ESC para terminar o programa */
	int i;
	switch (key)
	{
	case 'Q' :
	case 'q' :
	case 27  :  exit(EXIT_SUCCESS);
	case 'A':
		for (i = 0; i < 3; i++)
			if (models.kAmb[i] < 1)
				models.kAmb[i] += 0.1;
		fprintf(stdout, "Ambient coef: %f\n", models.kAmb[0]);
		glutPostRedisplay();
		break;
	case 'a':
		for (i = 0; i < 3; i++)
			if (models.kAmb[i] > 0)
				models.kAmb[i] -= 0.1;
		fprintf(stdout, "Ambient coef: %f\n", models.kAmb[0]);
		glutPostRedisplay();
		break;
	case 'D':
		for (i = 0; i < 3; i++)
			if (models.kDif[i] < 1)
				models.kDif[i] += 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", models.kDif[0]);
		glutPostRedisplay();
		break;
	case 'd':
		for (i = 0; i < 3; i++)
			if (models.kDif[i] > 0)
				models.kDif[i] -= 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", models.kDif[0]);
		glutPostRedisplay();
		break;
	case 'E':
		for (i = 0; i < 3; i++)
			if (models.kEsp[i] < 1)
				models.kEsp[i] += 0.1;
		fprintf(stdout, "Specular coef: %f\n", models.kEsp[0]);
		glutPostRedisplay();
		break;
	case 'e':
		for (i = 0; i < 3; i++)
			if (models.kEsp[i] > 0)
				models.kEsp[i] -= 0.1;
		fprintf(stdout, "Specular coef: %f\n", models.kEsp[0]);
		glutPostRedisplay();
		break;
	case 'P':
		if (models.coefPhong <= 20) 
			models.coefPhong++;
		else if (models.coefPhong < 255)
			models.coefPhong += 10;
		fprintf(stdout, "Phong coef: %f\n", models.coefPhong);
		glutPostRedisplay();
		break;
	case 'p':
		if (models.coefPhong <= 20 && models.coefPhong > 1) 
			models.coefPhong--;
		else if (models.coefPhong > 20)
			models.coefPhong -= 10;
		fprintf(stdout, "Phong coef: %f\n", models.coefPhong);
		glutPostRedisplay();
		break;
	case 'Z' :
	case 'z' :
		models.anguloRot.z += 5;
		if (models.anguloRot.z == 360.0)
		{
			models.anguloRot.z = 0.0;
		}
		glutPostRedisplay();
		break;
	case 'X' :
	case 'x' :
		models.anguloRot.z -= 5;
		if (models.anguloRot.z == -360.0)
		{
			models.anguloRot.z = 0.0;
		}
		glutPostRedisplay();
		break;
	case '+' :
		models.factorEsc.x *= 1.1;
		models.factorEsc.y *= 1.1;
		models.factorEsc.z *= 1.1;
		glutPostRedisplay();
		break;
	case '-' :
		models.factorEsc.x *= 0.9;
		models.factorEsc.y *= 0.9;
		models.factorEsc.z *= 0.9;
		glutPostRedisplay();
		break;
	}
}


void mySpecialKeys(int key, int x, int y)
{
	/* Usar as teclas de cursor para controlar as rotacoes */
	switch (key)
	{
	case GLUT_KEY_LEFT :
		models.anguloRot.y -= 5;
		if (models.anguloRot.y == -360.0)
		{
			models.anguloRot.y = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT :
		models.anguloRot.y += 5;
		if (models.anguloRot.y == 360.0)
		{
			models.anguloRot.y = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP :
		models.anguloRot.x -= 5;
		if (models.anguloRot.x == -360.0)
		{
			models.anguloRot.x = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN :
		models.anguloRot.x += 5;
		if (models.anguloRot.x == 360.0)
		{
			models.anguloRot.x = 0.0;
		}
		glutPostRedisplay();
		break;
	}
}


void myTimer(int value)
{
	if (animacaoON)
	{
		models.anguloRot.y += 5;
		if (models.anguloRot.y == 360.0)
		{
			models.anguloRot.y = 0.0;
		}
		glutPostRedisplay();
	}
	glutTimerFunc(250, myTimer, 0);
}


void registarCallbackFunctions(void)
{
	glutDisplayFunc(myDisplay);
	glutTimerFunc(250, myTimer, 0);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
}
