/*
 * init.c
 *
 * Ficheiro de implementacao do modulo INIT.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "mathUtils.hpp"
#include "models.hpp"

void inicializarEstado(void)
{
	/* DOUBLE-BUFFERING + DEPTH-TESTING */
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	/* Definir a cor do fundo */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	/* Atributos das primitivas */
	glPointSize(4.0);
	glLineWidth(3.0);
	/* Modo de desenho dos poligonos */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	/* Back-Face Culling */
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	/* Matriz de projeccao é inicialmente a IDENTIDADE => Proj. Paralela Ortogonal */
	matrizProj = IDENTITY_MATRIX;
	matrizModelView = IDENTITY_MATRIX;

	GraphicModelChess empty;
	models.insert(pair<int, GraphicModelChess>(0, empty));
}


void inicializarJanela(void)
{
	/* Caracteristicas da janela de saida */
	glutInitWindowSize(500, 500);   /* Usar variaveis GLOBAIS para estes parametros */
	glutInitWindowPosition(200, 200);
	/* Para terminar de modo apropriado */
	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);
	/* Criar a janela de saida */
	windowHandle = glutCreateWindow("OpenGL_ex_13");
	if (windowHandle < 1)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}
}

void inicializarFontesDeLuz(void)
{
	GraphicModelChess* obj = &models.find(0)->second;
	/* Intensidade Luminosa */
	// IL
	obj->intensidadeFLuz_0[0] = 1.0;
	obj->intensidadeFLuz_0[1] = 1.0;
	obj->intensidadeFLuz_0[2] = 1.0;
	obj->intensidadeFLuz_0[3] = 1.0;
	/* Posicao */
	obj->posicaoFLuz_0 [0] = 0.0;
	obj->posicaoFLuz_0 [1] = 0.0;
	obj->posicaoFLuz_0 [2] = 10.0;
	obj->posicaoFLuz_0 [3] = 0.0;
	/* Luz Ambiente */
	// IA
	obj->intensidadeLuzAmbiente[0] = 0.2;
	obj->intensidadeLuzAmbiente[1] = 0.2;
	obj->intensidadeLuzAmbiente[2] = 0.2;
	obj->intensidadeLuzAmbiente[3] = 1.0;
}

void inicializarModelos(void)
{
	GraphicModelChess* obj = &models.find(0)->second;
	lerVerticesDeFicheiro("models/queen.obj", &obj->numVertices, &obj->arrayVertices, &obj->arrayNormais);
	/* Determinar as normais unitarias a cada triangulo */
	//arrayNormais = calcularNormaisTriangulos(numVertices, arrayVertices);
	/* TESTE */
	//infosModelo( numVertices, arrayVertices, arrayNormais );
	/* Array vazio para guardar a cor atribuida a cada vertice */
	obj->arrayCores = (GLfloat *) calloc(3 * obj->numVertices, sizeof(GLfloat));
	
	/* Propriedades do material */
	obj->kAmb[0] = 0.2;
	obj->kAmb[1] = 0.2;
	obj->kAmb[2] = 0.2;
	obj->kAmb[3] = 1.0;

	obj->kDif[0] = 0.5;
	obj->kDif[1] = 0.5;
	obj->kDif[2] = 0.5;
	obj->kDif[3] = 1.0;

	obj->kEsp[0] = 0.7;
	obj->kEsp[1] = 0.7;
	obj->kEsp[2] = 0.7;
	obj->kEsp[3] = 1.0;
	obj->coefPhong = 100;
	/* Parametros das transformacoes */
	obj->desl.x = 0;
	obj->desl.y = 0;
	obj->desl.z = -0.5;
	obj->anguloRot.x = 0;
	obj->anguloRot.y = 0;
	obj->anguloRot.z = 0;
	obj->factorEsc.x = 0.25;
	obj->factorEsc.y = 0.25;
	obj->factorEsc.z = 0.25;
}

void libertarArraysGlobais(void)
{
	GraphicModelChess* obj = &models.find(0)->second;
	free(obj->arrayVertices);
	free(obj->arrayNormais);
	free(obj->arrayCores);
}
