/*
 * globals.h
 *
 * Declaracao de tipos e variaveis globais.
 *
 */


#ifndef GLOBALS_H
#define GLOBALS_H

#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include "utils/mathUtils.hpp"
#include "GraphicModelChess.hpp"
#include "LightModel.hpp"
#include "chess-engine/Chess.hpp"

using namespace std;

struct projCoord
{
	float fovy;
	float aspect_ratio;
	float near_plane;
	float far_plane;
};

/* Static variables */
static string projectPath = "../src/";
/* Global variables */
extern projCoord proj;
extern int windowHandle;
extern GLuint programaGLSL;
extern GLuint vs, fs;
extern GLint attribute_coord3d, attribute_normal3d, attribute_texcoord;
extern mat4x4 matrizProj, matrizModelView;

extern int selectedModel, selectedPosition;
extern Chess * chess;
extern LightModel * lights;
extern GraphicModelChess *chessTable, *selectedFrame, *skybox;
extern vector<GraphicModelChess*> previewPositions;
extern vector<GraphicModelChess> pieceModels;
extern Point2D<int> curr, last;
extern Point3D<float> tableRotation;
extern bool animationActive;
#endif
