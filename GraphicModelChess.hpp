#ifndef GRAPHICMODELCHESS_H
#define GRAPHICMODELCHESS_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "chess-engine/ChessPiece.hpp"
#include "models.hpp"
#include "utils/mathUtils.hpp"
#include "utils/Points.hpp"

class GraphicModelChess
{
public:
    /* Coordenadas dos vertices */
    ChessPiece *piece;

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

    /* -1.75 -1.25 -0.75 -0.25 0.25 0.75 1.25 1.75 */
    static Point2D<float> convertChessPos(Point2D<int> pos)
    {
        Point2D<float> point;
        point.x = pos.x * 0.5 - 1.75;
        point.y = pos.y * 0.5 - 1.75;
        return point;
    };
    static Point2D<float> convertBackToChessPos(float x, float y)
    {
        Point2D<float> point;
        point.x = (y + 1.75) / 0.5;
        point.y = (x + 1.75) / 0.5;
        return point;
    };
    static GraphicModelChess generatePreviewSquare(Point2D<float> p, float R, float G, float B) {
    	GraphicModelChess * obj = new GraphicModelChess();
		obj->piece = NULL;
		lerVerticesDeFicheiro("models/marker.obj", &obj->numVertices, &obj->arrayVertices, &obj->arrayNormais);
		obj->arrayCores = (GLfloat *) calloc(3 * obj->numVertices, sizeof(GLfloat));
		for (int i = 0; i < 3 * obj->numVertices; i+=3) {
			obj->arrayCores[i] = 1;
			obj->arrayCores[i+1] = 0;
			obj->arrayCores[i+2] = 0;
		}
		obj->kAmb[0] = 0.1 + 0.9 * R;
		obj->kAmb[1] = 0.1 + 0.9 * G;
		obj->kAmb[2] = 0.1 + 0.9 * B;
		obj->kAmb[3] = 1.0;
		obj->kDif[0] = 0.64;
		obj->kDif[1] = 0.64;
		obj->kDif[2] = 0.64;
		obj->kDif[3] = 1.0;
		obj->kEsp[0] = 0.9;
		obj->kEsp[1] = 0.9;
		obj->kEsp[2] = 0.9;
		obj->kEsp[3] = 1.0;
		obj->coefPhong = 100;
		obj->desl.x = p.x;
		obj->desl.y = p.y;
		obj->desl.z = 0.01;
		obj->anguloRot.x = 0;
		obj->anguloRot.y = 0;
		obj->anguloRot.z = 0;
		obj->factorEsc.x = 1;
		obj->factorEsc.y = 1;
		obj->factorEsc.z = 1;
		return *obj;
    }
};

#endif