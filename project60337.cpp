/*
 * OpenGL_ex_13.c
 *
 * Primeiro exemplo de iluminação - Per Vertex Shading !!
 *
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "callbacks.hpp"
#include "consoleIO.hpp"
#include "init.hpp"
#include "menus.hpp"
#include "shaders/shaders.hpp"

int main(int argc, char **argv)
{
	GLenum glewInitResult;
	/* Inicializacao do GLUT */
	glutInit(&argc, argv);
	inicializarJanela();
	/* Criar os menus */
	criarMenus();
	/* Inicializacao do GLEW */
	glewInitResult = glewInit();
	if (GLEW_OK != glewInitResult)
	{
		fprintf(
		    stderr,
		    "ERROR: %s\n",
		    glewGetErrorString(glewInitResult)
		);
		exit(EXIT_FAILURE);
	}
	/* Qual a versao do OpenGL? */
	fprintf(
	    stdout,
	    "INFO: OpenGL Version: %s\n",
	    glGetString(GL_VERSION)
	);
	/* Inicializar o estado da aplicacao */
	inicializarEstado();
	/* Inicializar a cena */
	inicializarPlanoProjeccao();
	inicializarModelos();
	inicializarFontesDeLuz();
	/* Inicializar os shaders */
	if (initResources() == 1)
	{
		/* Registando callback functions se OK */
		registarCallbackFunctions();
		infosConsola();
		glutMainLoop();
	}
	/* Housekeeping */
	freeResources();
	libertarArraysGlobais();
	return EXIT_SUCCESS;
}
