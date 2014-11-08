/*
 * globals.h
 *
 * Declaracao de tipos e variaveis globais.
 *
 */


#ifndef _globals_h
#define _globals_h

#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
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
/* Variaveis GLOBAIS !! */
extern projCoord proj;
extern int windowHandle;
/* O identificador do programa em GLSL combinando os SHADERS */
extern GLuint programaGLSL;
/* Os identificadores dos SHADERS */
extern GLuint vs;
extern GLuint fs;
/* Para passar coordenadas, cores a a matriz de transformacao ao Vertex-Shader */
extern GLint attribute_coord3d;
extern GLint attribute_corRGB;
extern GLint uniform_matriz_proj;
extern GLint uniform_matriz_model_view;
/* Matriz de projeccao */
extern mat4x4 matrizProj;
/* Matriz global de transformacao */
extern mat4x4 matrizModelView;

extern int selectedModel;
extern Chess * chess;
extern LightModel * lights;
extern vector<GraphicModelChess> previewPositions;
extern vector<GraphicModelChess> secondaryModels;
extern vector<GraphicModelChess> pieceModels;

#endif
