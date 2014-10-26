/*
 * consoleIO.c
 *
 * Ficheiro de implementacao do modulo CONSOLEIO.
 *
 */

/* Incluir os ficheiros cabecalhos necessarios */

#include <stdio.h>
#include "consoleIO.h"

/* Escrever algumas informacoes na consola */

void infosConsola(void)
{
	fprintf(stdout, "\n Para Terminar: usar as teclas Q ou ESC\n\n");
}


void infosModelo(int numVertices, GLfloat *arrayVertices, GLfloat *arrayNormais)
{
	int i;
	int j;
	fprintf(stdout, "Numero de Vertices = %d\n", numVertices);
	for (i = 0; i < numVertices; i++)
	{
		fprintf(stdout, "v[%d] = ", i);
		for (j = 0; j < 3; j++)
		{
			fprintf(stdout, "%f ", arrayVertices[ 3 * i + j ]);
		}
		fprintf(stdout, "\n");
		fprintf(stdout, "n[%d] = ", i);
		for (j = 0; j < 3; j++)
		{
			fprintf(stdout, "%f ", arrayNormais[ 3 * i + j ]);
		}
		fprintf(stdout, "\n");
	}
}


void infosVector(GLfloat *v)
{
	int j;
	for (j = 0; j < 3; j++)
	{
		fprintf(stdout, "%f ", v[ j ]);
	}
	fprintf(stdout, "\n");
}

/* Recolher os parametros das transformacoes */

void anguloRotacao(float *ang)
{
	fprintf(stdout, "\n\n Angulo de Rotacao em GRAUS : ");
	fscanf(stdin, "%f", ang);
	fprintf(stdout, "\n");
}


void parametrosTransl3D(float *dx, float *dy, float *dz)
{
	fprintf(stdout, "\n\n Translacao ( dx dy dz ) : ");
	fscanf(stdin, "%f%f%f", dx, dy, dz);
	fprintf(stdout, "\n");
}


void parametrosVarEscala3D(float *sx, float *sy, float *sz)
{
	fprintf(stdout, "\n\n Variacao de Escala ( sx xy sz ) : ");
	fscanf(stdin, "%f%f%f", sx, sy, sz);
	fprintf(stdout, "\n");
}


void nomeFicheiro(char *nome)
{
	fprintf(stdout, "Escreva o nome do ficheiro, incluindo a extensao:\n");
	fgets(nome, sizeof(nome), stdin);
}