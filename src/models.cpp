 /*
 * models.c
 *
 * Ficheiro de implementacao do modulo MODELS.
 *
 */


/* Incluir os ficheiros cabecalhos necessarios */


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include "models.hpp"
#include "utils/mathUtils.hpp"
#include "utils/Points.hpp"

void lerVerticesDeFicheiro(string nome, int *numVertices, vector<float> *arrayVertices, vector<float> *arrayNormais)
{
	std::vector<Point3D<float> > vertices, normalVector, faces, facesNormals;

	FILE * file = fopen(nome.c_str(), "r");
	if(file == NULL){
	    printf("Failed to open file!\n");
	    return;
	}

	char firstChar[128];
	int res = fscanf(file, "%s", firstChar);

	Point3D<float> tmp, tmpN;
	while(res != EOF) {
	    if (strcmp(firstChar, "v") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    vertices.push_back(tmp);
		} else if(strcmp(firstChar, "vn") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    normalVector.push_back(tmp);
		} else if(strcmp(firstChar, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
																	   &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
																	   &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    faces.push_back(vertices.at(vertexIndex[0]-1));
		    faces.push_back(vertices.at(vertexIndex[1]-1));
		    faces.push_back(vertices.at(vertexIndex[2]-1));

		    facesNormals.push_back(normalVector.at(normalIndex[0]-1));
		    facesNormals.push_back(normalVector.at(normalIndex[1]-1));
		    facesNormals.push_back(normalVector.at(normalIndex[2]-1));
		} else {

		}
		res = fscanf(file, "%s", firstChar);
	}

	*numVertices = faces.size();
	int i;
	int sub = 0;
	for (i = 0; i < faces.size(); i++) {
		tmp = faces.at(i);
		tmpN = facesNormals.at(i);

		arrayNormais->push_back(tmpN.x);
		arrayVertices->push_back(tmp.x);
		arrayNormais->push_back(tmpN.y);
		arrayVertices->push_back(tmp.y);
		arrayNormais->push_back(tmpN.z);
		arrayVertices->push_back(tmp.z);
	}
}


void escreverVerticesEmFicheiro(char *nome, int numVertices, GLfloat *arrayVertices)
{
	int i;
	int j;
	int indexArrayCoords;
	FILE *fp = fopen(nome, "w");
	if (fp == NULL)
	{
		fprintf(stderr, "ERRO na escrita do ficheiro %s\n", nome);
		exit(EXIT_FAILURE);
	}
	/* Escrever o numero de vertices */
	fprintf(fp, "%d\n", numVertices);
	/* Percorrer os arrays */
	/* Coordenadas ( x, y, z ) dos vertices */
	indexArrayCoords = 0;
	for (i = 0; i < numVertices; i++)
	{
		for (j = 0; j < 3; j++)
		{
			fprintf(fp, "%f ", arrayVertices[ indexArrayCoords++ ]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}


GLfloat *calcularNormaisTriangulos(int numVertices, GLfloat *arrayVertices)
{
	GLfloat *arrayNormais = (GLfloat *) malloc(3 * numVertices * sizeof(GLfloat));
	int index = 0; /* Indice para o proximo elemento */
	int j = 0;
	/* Para cada face triangular do modelo */
	for (index = 0; index < (3 * numVertices); index += 9)
	{
		GLfloat *normalVector;
		normalVector = computeUnitNormalToTriangle(&arrayVertices[index]);
		/* Store the unit normal vector for each vertex */
		for (j = 0; j < 3; j++)
		{
			arrayNormais[index + j] = normalVector[j];
			arrayNormais[index + j + 3] = normalVector[j];
			arrayNormais[index + j + 6] = normalVector[j];
		}
		free(normalVector);
	}
	return arrayNormais;
}

