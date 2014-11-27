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
    GraphicModelChess();
    ~GraphicModelChess();
    
    template<class T> static Point2D<float> convertChessPos(Point2D<T> pos) {
        Point2D<float> point;
        point.x = pos.x * 0.5 - 1.75;
        point.y = pos.y * 0.5 - 1.75;
        return point;
    }
    static Point2D<float> convertBackToChessPos(float, float);
    static GraphicModelChess* generatePreviewSquare(Point2D<float>, float, float, float, float, float);

    ChessPiece *piece;
    int numVertices;
    vector<float> arrayVertices;
    vector<float> arrayNormais;
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