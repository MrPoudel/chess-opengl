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
#include "globals.h"
#include "mathUtils.h"
#include "models.h"

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
	/* Para rodar globalmente a cena */
	animacaoON = 0;
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
	/* Intensidade Luminosa */
	// IL
	intensidadeFLuz_0 = (GLfloat *) malloc(4 * sizeof(GLfloat));
	intensidadeFLuz_0[0] = 1.0;
	intensidadeFLuz_0[1] = 1.0;
	intensidadeFLuz_0[2] = 1.0;
	intensidadeFLuz_0[3] = 1.0;
	/* Posicao */
	posicaoFLuz_0 = (GLfloat *) malloc(4 * sizeof(GLfloat));
	posicaoFLuz_0 [0] = 0.0;
	posicaoFLuz_0 [1] = 0.0;
	posicaoFLuz_0 [2] = 10.0;
	posicaoFLuz_0 [3] = 0.0;
	/* Luz Ambiente */
	// IA
	intensidadeLuzAmbiente = (GLfloat *) malloc(4 * sizeof(GLfloat));
	intensidadeLuzAmbiente[0] = 0.2;
	intensidadeLuzAmbiente[1] = 0.2;
	intensidadeLuzAmbiente[2] = 0.2;
	intensidadeLuzAmbiente[3] = 1.0;
}

void inicializarModelos(void)
{
	lerVerticesDeFicheiro("modeloCuboV4.txt", &numVertices, &arrayVertices);
	/* Determinar as normais unitarias a cada triangulo */
	//arrayNormais = calcularNormaisTriangulos(numVertices, arrayVertices);
	/* TESTE */
	//infosModelo( numVertices, arrayVertices, arrayNormais );
	/* Array vazio para guardar a cor atribuida a cada vertice */
	arrayCores = (GLfloat *) calloc(3 * numVertices, sizeof(GLfloat));
	/* Propriedades do material */
	kAmb = (GLfloat *) malloc(4 * sizeof(GLfloat));
	kAmb[0] = 0.2;
	kAmb[1] = 0.2;
	kAmb[2] = 0.2;
	kAmb[3] = 1.0;
	kDif = (GLfloat *) malloc(4 * sizeof(GLfloat));
	kDif[0] = 0.5;
	kDif[1] = 0.5;
	kDif[2] = 0.5;
	kDif[3] = 1.0;
	kEsp = (GLfloat *) malloc(4 * sizeof(GLfloat));
	kEsp[0] = 0.7;
	kEsp[1] = 0.7;
	kEsp[2] = 0.7;
	kEsp[3] = 1.0;
	coefPhong = 100;
	/* Parametros das transformacoes */
	deslX = 0;
	deslY = 0;
	deslZ = -0.5;
	anguloRotXX = 0;
	anguloRotYY = 0;
	anguloRotZZ = 0;
	factorEscX = 0.25;
	factorEscY = 0.25;
	factorEscZ = 0.25;
}

void libertarArraysGlobais(void)
{
	free(arrayVertices);
	free(arrayNormais);
	free(arrayCores);
}
