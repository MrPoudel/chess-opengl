#ifndef GRAPHICMODELCHESS_H
#define GRAPHICMODELCHESS_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "chess-engine/ChessPiece.hpp"
#include "utils/mathUtils.hpp"
#include "utils/Points.hpp"

class GraphicModelChess {
public:
	/* Coordenadas dos vertices */
	ChessPiece * piece;

	int numVertices;
	float *arrayVertices;
	float *arrayNormais;
	float *arrayCores;
	/* Propriedades do material */
	float kAmb[4];
	float kDif[4];
	float kEsp[4];
	float coefPhong;
	/* Parametros das transformacoes */
	Point3D<float> desl;
	Point3D<float> anguloRot;
	Point3D<float> factorEsc;
};

#endif