#include "globals.hpp"

using namespace std;

/* Variaveis GLOBAIS !! */
projCoord proj;
int windowHandle;
/* O identificador do programa em GLSL combinando os SHADERS */
GLuint programaGLSL;
/* Os identificadores dos SHADERS */
GLuint vs, fs;
/* Para passar coordenadas, cores a a matriz de transformacao ao Vertex-Shader */
GLint attribute_coord3d, attribute_normal3d, attribute_texcoord;
/* Matriz de projeccao e Matriz global de transformacao */
mat4x4 matrizProj, matrizModelView;

Chess * chess;
LightModel * lights;
int selectedModel, selectedPosition;
GraphicModelChess * chessTable, * selectedFrame, * skybox;
vector<GraphicModelChess*> previewPositions;
vector<GraphicModelChess> pieceModels;

Point2D<int> curr = {0,0}, last = {0,0};
bool arcball_on = false;

Point3D<int> tableRotation;
