#include "globals.h"

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
/* Para o FOCO PONTUAL */
GLfloat *intensidadeFLuz_0;
GLfloat *posicaoFLuz_0;
GLfloat *intensidadeLuzAmbiente;
/* Para o modelo corrente */
/* Coordenadas dos vertices */
GLsizei numVertices;
GLfloat *arrayVertices;
GLfloat *arrayNormais;
GLfloat *arrayCores;
/* Propriedades do material */
GLfloat *kAmb;
GLfloat *kDif;
GLfloat *kEsp;
GLfloat coefPhong;
/* Matriz global de transformacao */
mat4x4 matrizModelView;
/* Parametros das transformacoes */
GLfloat deslX;
GLfloat deslY;
GLfloat deslZ;
GLfloat anguloRotXX;
GLfloat anguloRotYY;
GLfloat anguloRotZZ;
GLfloat factorEscX;
GLfloat factorEscY;
GLfloat factorEscZ;
/* FLAG para controlar a animacao */
GLboolean animacaoON;
