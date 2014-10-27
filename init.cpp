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
	models.intensidadeFLuz_0[0] = 1.0;
	models.intensidadeFLuz_0[1] = 1.0;
	models.intensidadeFLuz_0[2] = 1.0;
	models.intensidadeFLuz_0[3] = 1.0;
	/* Posicao */
	models.posicaoFLuz_0 [0] = 0.0;
	models.posicaoFLuz_0 [1] = 0.0;
	models.posicaoFLuz_0 [2] = 10.0;
	models.posicaoFLuz_0 [3] = 0.0;
	/* Luz Ambiente */
	// IA
	models.intensidadeLuzAmbiente[0] = 0.2;
	models.intensidadeLuzAmbiente[1] = 0.2;
	models.intensidadeLuzAmbiente[2] = 0.2;
	models.intensidadeLuzAmbiente[3] = 1.0;
}

void inicializarModelos(void)
{
	lerVerticesDeFicheiro("models/queen.obj", &models.numVertices, &models.arrayVertices, &models.arrayNormais);
	/* Determinar as normais unitarias a cada triangulo */
	//arrayNormais = calcularNormaisTriangulos(numVertices, arrayVertices);
	/* TESTE */
	//infosModelo( numVertices, arrayVertices, arrayNormais );
	/* Array vazio para guardar a cor atribuida a cada vertice */
	models.arrayCores = (GLfloat *) calloc(3 * models.numVertices, sizeof(GLfloat));
	
	/* Propriedades do material */
	models.kAmb[0] = 0.2;
	models.kAmb[1] = 0.2;
	models.kAmb[2] = 0.2;
	models.kAmb[3] = 1.0;

	models.kDif[0] = 0.5;
	models.kDif[1] = 0.5;
	models.kDif[2] = 0.5;
	models.kDif[3] = 1.0;

	models.kEsp[0] = 0.7;
	models.kEsp[1] = 0.7;
	models.kEsp[2] = 0.7;
	models.kEsp[3] = 1.0;
	models.coefPhong = 100;
	/* Parametros das transformacoes */
	models.desl.x = 0;
	models.desl.y = 0;
	models.desl.z = -0.5;
	models.anguloRot.x = 0;
	models.anguloRot.y = 0;
	models.anguloRot.z = 0;
	models.factorEsc.x = 0.25;
	models.factorEsc.y = 0.25;
	models.factorEsc.z = 0.25;
}

void libertarArraysGlobais(void)
{
	free(models.arrayVertices);
	free(models.arrayNormais);
	free(models.arrayCores);
}
