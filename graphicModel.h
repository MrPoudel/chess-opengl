#ifndef _graphicmodel_h
#define _graphicmodel_h

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "mathUtils.h"

struct point3D
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

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
	point3D desl;
	point3D anguloRot;
	point3D factorEsc;
};

#endif