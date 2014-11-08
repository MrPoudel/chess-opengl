/*
 * models.h
 *
 * Ficheiro cabecalho do modulo MODELS.
 *
 */


#ifndef _models_h
#define _models_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

using namespace std;

void lerVerticesDeFicheiro(string nome, int *numVertices, GLfloat **arrayVertices, GLfloat **arrayNormais);
void escreverVerticesEmFicheiro(string nome, int numVertices, GLfloat *arrayVertices);
GLfloat *calcularNormaisTriangulos(int numVertices, GLfloat *arrayVertices);

#endif
