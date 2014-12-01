/*
 * menus.c
 *
 * Ficheiro de implementacao do modulo MENUS.
 *
 */


/* Incluir os ficheiros cabecalhos necessarios */

#include <stdlib.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "consoleIO.hpp"
#include "globals.hpp"
#include "init.hpp"
#include "menus.hpp"
#include "models.hpp"

#include <string>
using namespace std;


/* ----------------------------------------------------------------------- */

/* Definicao dos menus e sub-menus usando um tipo auxiliar e arrays */

/* Ref.: "OpenGL: A Primer" - p. 219-220 */

typedef struct menuItemStruct
{
	string item; /* O texto do item */
	char  val;  /* O valor retornado */
} menuItemStruct;

/* Menu 2 - Botao Direito */
static menuItemStruct menu2[] =
{
	{"Faces",               'F'},
	{"Arestas",             'A'},
	{"Vertices",            'V'},
	{"-----------------",   '-'},
	{"Sair",                '9'}
};

int numItensMenu2 = sizeof(menu2) / sizeof(menuItemStruct);


/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */
static void myMenuDir(int i)
{
	GraphicModelChess * obj = &pieceModels[0];
	char nomeF[40];
	switch (menu2[i].val)
	{
	case 'F' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'A' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glutPostRedisplay();
		break;
	case 'V' :
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutPostRedisplay();
		break;
	case '9' :
		exit(EXIT_SUCCESS);
		break;
	}
}

/* Criar os menus */

void criarMenus(void)
{
	int i;
	glutCreateMenu(myMenuDir);
	for (i = 0; i < numItensMenu2; i++) {
		glutAddMenuEntry(menu2[i].item.c_str(), i);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


