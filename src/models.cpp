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

using namespace std;

GLuint loadBMPImage(string imagepath) {
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;

	FILE * file = fopen(imagepath.c_str(),"rb");
	if (!file) {
		cout << "Image could not be opened" << endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
    	cout << "Not a correct BMP file" << endl;
    	return false;
	}
	if (header[0] != 'B' || header[1] != 'M') {
	    cout << "Not a correct BMP file" << endl;
	    return 0;
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	if (imageSize == 0)    
		imageSize = width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      
		dataPos = 54; // The BMP header is done that way

	data = new unsigned char[imageSize];
	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);
	// Everything is in memory now, the file can be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	// Give the image to OpenGL
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete[] data;
	return textureID;
}
void lerVerticesDeFicheiro(string nome, int *numVertices, vector<float> *arrayVertices, 
										vector<float> *arrayNormais, vector<float> *arrayTextures)
{
	std::vector<Point3D<float> > vertices, normalVector, faces, facesNormals;
	std::vector<Point2D<float> > textureVector, facesTextures;

	FILE * file = fopen(nome.c_str(), "r");
	if(file == NULL){
	    printf("Failed to open file!\n");
	    return;
	}

	char firstChar[128];
	int res = fscanf(file, "%s", firstChar);

	Point3D<float> tmp, tmpN;
	Point2D<float> tmpT;
	while(res != EOF) {
	    if (strcmp(firstChar, "v") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    vertices.push_back(tmp);
		} else if(strcmp(firstChar, "vn") == 0) {
		    fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
		    normalVector.push_back(tmp);
		} else if(strcmp(firstChar, "vt") == 0) {
			fscanf(file, "%f %f\n", &tmpT.x, &tmpT.y);
			textureVector.push_back(tmpT);
		} else if(strcmp(firstChar, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
																	   &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
																	   &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
		    faces.push_back(vertices.at(vertexIndex[0]-1));
		    faces.push_back(vertices.at(vertexIndex[1]-1));
		    faces.push_back(vertices.at(vertexIndex[2]-1));

		    facesTextures.push_back(textureVector.at(uvIndex[0]-1));
		    facesTextures.push_back(textureVector.at(uvIndex[1]-1));
		    facesTextures.push_back(textureVector.at(uvIndex[2]-1));

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
		tmpT = facesTextures.at(i);

		arrayNormais->push_back(tmpN.x);
		arrayNormais->push_back(tmpN.y);
		arrayNormais->push_back(tmpN.z);

		arrayTextures->push_back(tmpT.x);
		arrayTextures->push_back(tmpT.y);

		arrayVertices->push_back(tmp.x);
		arrayVertices->push_back(tmp.y);
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

