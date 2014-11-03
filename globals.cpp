#include "globals.hpp"

using namespace std;
/* Variaveis GLOBAIS !! */
int windowHandle;
/* O identificador do programa em GLSL combinando os SHADERS */
GLuint programaGLSL;
/* Os identificadores dos SHADERS */
GLuint vs;
GLuint fs;
/* Para passar coordenadas, cores a a matriz de transformacao ao Vertex-Shader */
GLint attribute_coord3d;
GLint attribute_corRGB;
GLint uniform_matriz_proj;
GLint uniform_matriz_model_view;
/* Matriz de projeccao */
mat4x4 matrizProj;
/* Matriz global de transformacao */
mat4x4 matrizModelView;

Chess * chess;
LightModel * lights;
int selectedModel;
vector<GraphicModelChess> models;
