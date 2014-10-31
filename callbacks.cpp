/*
 * callbacks.c
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "callbacks.hpp"
#include "consoleIO.hpp"

/* Callback functions */

void myDisplay(void)
{
	/* Limpar a janela */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* SHADERS */
	glUseProgram(programaGLSL);
	/* Input para o Vertex-Shader */
	for (int modelId = 0; modelId < models.size(); modelId++)
	{
		GraphicModelChess *obj = &models[modelId];
		glEnableVertexAttribArray(attribute_coord3d);
		glEnableVertexAttribArray(attribute_corRGB);
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
		/* Caracteristicas do array de coordenadas */
		glVertexAttribPointer(attribute_coord3d,  // attribute
							  3,                 // number of elements per vertex, here (x,y,z)
							  GL_FLOAT,          // the type of each element
							  GL_FALSE,          // take our values as-is
							  0,                 // no extra data between each position
							  obj->arrayVertices);    // pointer to the C array
		/* Caracteristicas do array de cores */
		glVertexAttribPointer(attribute_corRGB,  // attribute
							  3,                 // number of elements per vertex, here (R,G,B)
							  GL_FLOAT,          // the type of each element
							  GL_FALSE,          // take our values as-is
							  0,                 // no extra data between each position
							  obj->arrayCores);     // pointer to the C array
		/* ATENCAO : Ordem das transformacoes !! */
		matrizModelView = IDENTITY_MATRIX;
		/* Deslocar para mais longe */
		Translate(&matrizModelView, obj->desl.x, obj->desl.y, obj->desl.z);
		RotateAboutX(&matrizModelView, DegreesToRadians(obj->anguloRot.x));
		RotateAboutY(&matrizModelView, DegreesToRadians(obj->anguloRot.y));
		RotateAboutZ(&matrizModelView, DegreesToRadians(obj->anguloRot.z));
		/* Diminuir o tamanho do modelo para nao sair fora do view volume */
		Scale(&matrizModelView, obj->factorEsc.x, obj->factorEsc.y, obj->factorEsc.z);
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
			ambientTerm[i] = obj->kAmb[i] * lights->intensidadeLuzAmbiente[i]; /* TESTING */
			diffuseTerm[i] = obj->kDif[i] * lights->intensidadeFLuz[i];
			specularTerm[i] = obj->kEsp[i] * lights->intensidadeFLuz[i];
		}
		/* SMOOTH-SHADING */
		/* Compute the illumination RGB value for every triangle vertex */
		/* Store the RGB values in the color array */
		indexArrayCores = 0;
		GLfloat normalDifuse = 0;
		GLfloat normalSpecular = 0;
		for (indexArrayVertices = 0; indexArrayVertices < (3 * obj->numVertices); indexArrayVertices += 3)
		{
			/* For every vertex */
			/* Get the XYZ coordinates and the normal vector */
			for (i = 0; i < 3; i++)
			{
				auxP[i] = obj->arrayVertices[ indexArrayVertices + i ];
				auxN[i] = obj->arrayNormais[ indexArrayVertices + i ];
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
				vectorL[i] = lights->posicaoFLuz[i];
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

			obj->arrayCores[indexArrayCores] = modelId % 3 / 2;//ambientTerm[0] + diffuseTerm[0] * cosNL + specularTerm[0] * pow(cosNH, obj->coefPhong);
			obj->arrayCores[indexArrayCores] = ambientTerm[0] + diffuseTerm[0] * cosNL + specularTerm[0] * pow(cosNH, obj->coefPhong);
			indexArrayCores++;
			obj->arrayCores[indexArrayCores] = 1; //ambientTerm[1] + diffuseTerm[1] * cosNL + specularTerm[1] * pow(cosNH, obj->coefPhong);
			obj->arrayCores[indexArrayCores] = ambientTerm[1] + diffuseTerm[1] * cosNL + specularTerm[1] * pow(cosNH, obj->coefPhong);
			indexArrayCores++;
			obj->arrayCores[indexArrayCores] = 1;//ambientTerm[2] + diffuseTerm[2] * cosNL + specularTerm[2] * pow(cosNH, obj->coefPhong);
			obj->arrayCores[indexArrayCores] = ambientTerm[2] + diffuseTerm[2] * cosNL + specularTerm[2] * pow(cosNH, obj->coefPhong);
			indexArrayCores++;
			/* Libertar os arrays temporarios */
			free(pontoP);
			free(vectorN);
			free(vectorV);
			free(vectorH);
		}
		/* Push each element to the vertex shader */
		glDrawArrays(GL_TRIANGLES, 0, obj->numVertices);
		glDisableVertexAttribArray(attribute_coord3d);
		glDisableVertexAttribArray(attribute_corRGB);
	}
	/* Display the result */
	/* DOUBLE-BUFFERING */
	glutSwapBuffers();
}


void myKeyboard(unsigned char key, int x, int y)
{
	/* Usar as teclas Q ou ESC para terminar o programa */
	int i;
	GraphicModelChess *obj = &models[1];
	switch (key)
	{
	case 'Q' :
	case 'q' :
	case 27  :  exit(EXIT_SUCCESS);
	case 'y':
		obj->desl.y += 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 't':
		obj->desl.x += 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 'u':
		obj->desl.z += 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 'Y':
		obj->desl.y -= 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 'T':
		obj->desl.x -= 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 'U':
		obj->desl.z -= 0.05;
		fprintf(stdout, "%f %f %f\n", obj->desl.x, obj->desl.y, obj->desl.z );
		glutPostRedisplay();
		break;
	case 'A':
		for (i = 0; i < 3; i++)
			if (obj->kAmb[i] < 1)
				obj->kAmb[i] += 0.1;
		fprintf(stdout, "Ambient coef: %f\n", obj->kAmb[0]);
		glutPostRedisplay();
		break;
	case 'a':
		for (i = 0; i < 3; i++)
			if (obj->kAmb[i] > 0)
				obj->kAmb[i] -= 0.1;
		fprintf(stdout, "Ambient coef: %f\n", obj->kAmb[0]);
		glutPostRedisplay();
		break;
	case 'D':
		for (i = 0; i < 3; i++)
			if (obj->kDif[i] < 1)
				obj->kDif[i] += 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", obj->kDif[0]);
		glutPostRedisplay();
		break;
	case 'd':
		for (i = 0; i < 3; i++)
			if (obj->kDif[i] > 0)
				obj->kDif[i] -= 0.1;
		fprintf(stdout, "Diffuse coef: %f\n", obj->kDif[0]);
		glutPostRedisplay();
		break;
	case 'E':
		for (i = 0; i < 3; i++)
			if (obj->kEsp[i] < 1)
				obj->kEsp[i] += 0.1;
		fprintf(stdout, "Specular coef: %f\n", obj->kEsp[0]);
		glutPostRedisplay();
		break;
	case 'e':
		for (i = 0; i < 3; i++)
			if (obj->kEsp[i] > 0)
				obj->kEsp[i] -= 0.1;
		fprintf(stdout, "Specular coef: %f\n", obj->kEsp[0]);
		glutPostRedisplay();
		break;
	case 'P':
		if (obj->coefPhong <= 20)
			obj->coefPhong++;
		else if (obj->coefPhong < 255)
			obj->coefPhong += 10;
		fprintf(stdout, "Phong coef: %f\n", obj->coefPhong);
		glutPostRedisplay();
		break;
	case 'p':
		if (obj->coefPhong <= 20 && obj->coefPhong > 1)
			obj->coefPhong--;
		else if (obj->coefPhong > 20)
			obj->coefPhong -= 10;
		fprintf(stdout, "Phong coef: %f\n", obj->coefPhong);
		glutPostRedisplay();
		break;
	case 'Z' :
	case 'z' :
		obj->anguloRot.z += 5;
		if (obj->anguloRot.z == 360.0)
		{
			obj->anguloRot.z = 0.0;
		}
		glutPostRedisplay();
		break;
	case 'X' :
	case 'x' :
		obj->anguloRot.z -= 5;
		if (obj->anguloRot.z == -360.0)
		{
			obj->anguloRot.z = 0.0;
		}
		glutPostRedisplay();
		break;
	case '+' :
		obj->factorEsc.x *= 1.1;
		obj->factorEsc.y *= 1.1;
		obj->factorEsc.z *= 1.1;
		glutPostRedisplay();
		break;
	case '-' :
		obj->factorEsc.x *= 0.9;
		obj->factorEsc.y *= 0.9;
		obj->factorEsc.z *= 0.9;
		glutPostRedisplay();
		break;
	}
}


void mySpecialKeys(int key, int x, int y)
{
	/* Usar as teclas de cursor para controlar as rotacoes */
	GraphicModelChess *obj = &models[1];
	switch (key)
	{
	case GLUT_KEY_LEFT :
		obj->anguloRot.y -= 5;
		if (obj->anguloRot.y == -360.0)
		{
			obj->anguloRot.y = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT :
		obj->anguloRot.y += 5;
		if (obj->anguloRot.y == 360.0)
		{
			obj->anguloRot.y = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP :
		obj->anguloRot.x -= 5;
		if (obj->anguloRot.x == -360.0)
		{
			obj->anguloRot.x = 0.0;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN :
		obj->anguloRot.x += 5;
		if (obj->anguloRot.x == 360.0)
		{
			obj->anguloRot.x = 0.0;
		}
		glutPostRedisplay();
		break;
	}
}


void myTimer(int value)
{
	//printf("%d\n", glGetError());
	/*if (animacaoON)
	{
		models.anguloRot.y += 5;
		if (models.anguloRot.y == 360.0)
		{
			models.anguloRot.y = 0.0;
		}
		glutPostRedisplay();
	}*/
	glutTimerFunc(250, myTimer, 0);
}


void registarCallbackFunctions(void)
{
	glutDisplayFunc(myDisplay);
	glutTimerFunc(250, myTimer, 0);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
}
