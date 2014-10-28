#ifndef _graphicmodel_h
#define _graphicmodel_h

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathUtils.hpp"
#include "Points.hpp"

enum ChessPiece {
	Pawn, Tower, King, Queen, Bishop, Knight
};

class GraphicModelChess {
public:
	ChessPiece piece;
	/* Para o FOCO PONTUAL */
	GLfloat intensidadeFLuz_0[4];
	GLfloat posicaoFLuz_0[4];
	GLfloat intensidadeLuzAmbiente[4];
	/* Para o modelo corrente */
	/* Coordenadas dos vertices */
	GLsizei numVertices;
	GLfloat *arrayVertices;
	GLfloat *arrayNormais;
	GLfloat *arrayCores;
	/* Propriedades do material */
	GLfloat kAmb[4];
	GLfloat kDif[4];
	GLfloat kEsp[4];
	GLfloat coefPhong;
	/* Parametros das transformacoes */
	Point3D<float> desl;
	Point3D<float> anguloRot;
	Point3D<float> factorEsc;
};

#endif