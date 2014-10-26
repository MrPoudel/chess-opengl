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
						  arrayVertices);    // pointer to the C array
	/* Caracteristicas do array de cores */
	glVertexAttribPointer(attribute_corRGB,  // attribute
						  3,                 // number of elements per vertex, here (R,G,B)
						  GL_FLOAT,          // the type of each element
						  GL_FALSE,          // take our values as-is
						  0,                 // no extra data between each position
						  arrayCores);     // pointer to the C array
	/* ATENCAO : Ordem das transformacoes !! */
	matrizModelView = IDENTITY_MATRIX;
	/* Deslocar para mais longe */
	Translate(&matrizModelView, deslX, deslY, deslZ);
	RotateAboutX(&matrizModelView, DegreesToRadians(anguloRotXX));
	RotateAboutY(&matrizModelView, DegreesToRadians(anguloRotYY));
	RotateAboutZ(&matrizModelView, DegreesToRadians(anguloRotZZ));
	/* Diminuir o tamanho do modelo para nao sair fora do view volume */
	Scale(&matrizModelView, factorEscX, factorEscY, factorEscZ);
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
		ambientTerm[i] = kAmb[i] * intensidadeLuzAmbiente[i]; /* TESTING */
		diffuseTerm[i] = kDif[i] * intensidadeFLuz_0[i];
		specularTerm[i] = kEsp[i] * intensidadeFLuz_0[i];
	}
	/* SMOOTH-SHADING */
	/* Compute the illumination RGB value for every triangle vertex */
	/* Store the RGB values in the color array */
	indexArrayCores = 0;
	GLfloat normalDifuse = 0;
	GLfloat normalSpecular = 0;
	// for (indexArrayVertices = 0; indexArrayVertices < (3 * numVertices); indexArrayVertices += 3)
	// {
	// 	/* For every vertex */
	// 	/* Get the XYZ coordinates and the normal vector */
	// 	for (i = 0; i < 3; i++)
	// 	{
	// 		auxP[i] = arrayVertices[ indexArrayVertices + i ];
	// 		auxN[i] = arrayNormais[ indexArrayVertices + i ];
	// 	}
	// 	/* The 4th homogeneous coordinate */
	// 	auxP[3] = 1.0;
	// 	auxN[3] = 0.0;
	// 	/* Apply the global transformation matrix to each vertex */
	// 	pontoP = multiplyPointByMatrix(&matrizModelView, auxP);
	// 	/* And to the corresponding normal vector */
	// 	vectorN = multiplyVectorByMatrix(&matrizModelView, auxN);
	// 	/* Get the corresponding unit normal vector */
	// 	convertToUnitVector(vectorN);
	// 	/* DIFFUSE REFLECTION */
	// 	/* Compute the vector L */
	// 	for (i = 0; i < 3; i++)
	// 	{
	// 		vectorL[i] = posicaoFLuz_0[i];
	// 	}
	// 	/* TWO SITUATIONS : POINT light source versus DIRECTIONAL light source */
	// 	/* Get the corresponding unit vector */
	// 	convertToUnitVector(vectorL);
	// 	/* Compute cos (N . L) */
	// 	cosNL = computeScalarProduct(vectorN, vectorL);
	// 	 STOP and CHECK if you get the expected results 
	// 	/* SPECULAR REFLECTION */
	// 	/* Compute the vector V --- The viewer is at (0,0,0) */
	// 	vectorV = computeSymmetricVector(pontoP);
	// 	/* Compute the HALFWAY VECTOR */
	// 	vectorH = addVector(vectorL, vectorV);
	// 	/* Get the corresponding unit vector */
	// 	convertToUnitVector(vectorH);
	// 	/* Compute cos (N . H) */
	// 	cosNH = computeScalarProduct(vectorN, vectorH);
	// 	/* STOP and CHECK if you get the expected results */
	// 	/* ADD UP the 3 illumination components */
	// 	/* AVOID RGB values greater the 1.0 */
	// 	/* ONLY the AMBIENT component is being used at this moment... */
	// 	arrayCores[indexArrayCores] = ambientTerm[0] + diffuseTerm[0] * cosNL + specularTerm[0] * pow(cosNH, coefPhong);
	// 	indexArrayCores++;
	// 	arrayCores[indexArrayCores] = ambientTerm[1] + diffuseTerm[1] * cosNL + specularTerm[1] * pow(cosNH, coefPhong);
	// 	indexArrayCores++;
	// 	arrayCores[indexArrayCores] = ambientTerm[2] + diffuseTerm[2] * cosNL + specularTerm[2] * pow(cosNH, coefPhong);
	// 	indexArrayCores++;
	// 	/* Libertar os arrays temporarios */
	// 	free(pontoP);
	// 	free(vectorN);
	// 	free(vectorV);
	// 	free(vectorH);
	// }
	
	/* SMOOTH-SHADING */
	/* Compute the illumination RGB value for every triangle vertex */
	/* Store the RGB values in the color array */
	for (indexArrayVertices = 0; indexArrayVertices < (3 * numVertices); indexArrayVertices += 3)
	{
		arrayCores[indexArrayCores] = ambientTerm[0];
		indexArrayCores++;
		arrayCores[indexArrayCores] = ambientTerm[1];
		indexArrayCores++;
		arrayCores[indexArrayCores] = ambientTerm[2];
		indexArrayCores++;
		/* Libertar os arrays temporarios */
		free(pontoP);
		free(vectorN);
		free(vectorV);
		free(vectorH);
	}
	/* Push each element to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
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
			if (kAmb[i] < 1)
				kAmb[i] += 0.1;
		fprintf(stdout, "Ambient coef: %f\n", kAmb[0]);
		glutPostRedisplay();
		break;
	case 'a':
		for (i = 0; i < 3; i++)
			if (kAmb[i] > 0)
				kAmb[i] -= 0.1;
		fprintf(stdout, "Ambient coef: %f\n", kAmb[0]);
		glutPostRedisplay();
		break;
	case 'D':
		for (i = 0; i < 3; i++)
			if (kDif[i] < 1)
				kDif[i] += 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", kDif[0]);
		glutPostRedisplay();
		break;
	case 'd':
		for (i = 0; i < 3; i++)
			if (kDif[i] > 0)
				kDif[i] -= 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", kDif[0]);
		glutPostRedisplay();
		break;
	case 'E':
		for (i = 0; i < 3; i++)
			if (kEsp[i] < 1)
				kEsp[i] += 0.1;
		fprintf(stdout, "Specular coef: %f\n", kEsp[0]);
		glutPostRedisplay();
		break;
	case 'e':
		for (i = 0; i < 3; i++)
			if (kEsp[i] > 0)
				kEsp[i] -= 0.1;
		fprintf(stdout, "Specular coef: %f\n", kEsp[0]);
		glutPostRedisplay();
		break;
	case 'P':
		if (coefPhong < 255)
			coefPhong += 10;
		fprintf(stdout, "Phong coef: %f\n", coefPhong);
		glutPostRedisplay();
		break;
	case 'p':
		if (coefPhong > 1)
			coefPhong -= 10;
		glutPostRedisplay();
		break;
	case 'Z' :
	case 'z' :
		anguloRotZZ += 5;
		if (anguloRotZZ == 360.0)
		{
			anguloRotZZ = 0.0;
		}
		glutPostRedisplay();
		break;
	case 'X' :
	case 'x' :
		anguloRotZZ -= 5;
		if (anguloRotZZ == -360.0)
		{
			anguloRotZZ = 0.0;
		}
		glutPostRedisplay();
		break;
	case '+' :
		factorEscX *= 1.1;
		factorEscY *= 1.1;
		factorEscZ *= 1.1;
		glutPostRedisplay();
		break;
	case '-' :
		factorEscX *= 0.9;
		factorEscY *= 0.9;
		factorEscZ *= 0.9;
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
		anguloRotYY -= 5;
		if (anguloRotYY == -360.0)
		{
			anguloRotYY = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT :
		anguloRotYY += 5;
		if (anguloRotYY == 360.0)
		{
			anguloRotYY = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP :
		anguloRotXX -= 5;
		if (anguloRotXX == -360.0)
		{
			anguloRotXX = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN :
		anguloRotXX += 5;
		if (anguloRotXX == 360.0)
		{
			anguloRotXX = 0.0;
		}
		glutPostRedisplay();
		break;
	}
}


void myTimer(int value)
{
	if (animacaoON)
	{
		anguloRotYY += 5;
		if (anguloRotYY == 360.0)
		{
			anguloRotYY = 0.0;
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
