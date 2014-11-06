/*
 * callbacks.c
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include "globals.hpp"
#include "callbacks.hpp"
#include "consoleIO.hpp"

using namespace std;
/* Callback functions */
void myAnimationTimer(int value);
void produceModelsShading(GraphicModelChess *obj)
{
    glEnableVertexAttribArray(attribute_coord3d);
    glEnableVertexAttribArray(attribute_corRGB);
    int i;
    int indexArrayVertices;
    int indexArrayNormais;
    int indexArrayCores;
    float auxP[4];
    float *pontoP = NULL;
    float auxN[4];
    float *vectorN = NULL;
    float vectorL[4];
    float *vectorV = NULL;
    float *vectorH = NULL;
    float cosNL;
    float cosNH;
    GLfloat ambientTerm[3];
    GLfloat diffuseTerm[3];
    GLfloat specularTerm[3];
    /* Caracteristicas do array de coordenadas */
    glVertexAttribPointer(attribute_coord3d,  // attribute
                          3,                 // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,          // the type of each element
                          GL_FALSE,          // take our values as-is
                          0,                 // no extra data between each position
                          obj->arrayVertices);    // pointer to the C array
    /* Caracteristicas do array de cores */
    glVertexAttribPointer(attribute_corRGB,  // attribute
                          3,                 // number of elements per vertex, here (R,G,B)
                          GL_FLOAT,          // the type of each element
                          GL_FALSE,          // take our values as-is
                          0,                 // no extra data between each position
                          obj->arrayCores);     // pointer to the C array
    /* ATENCAO : Ordem das transformacoes !! */
    matrizModelView = IDENTITY_MATRIX;
    /* Deslocar para mais longe */
    Translate(&matrizModelView, obj->desl.x, obj->desl.y, obj->desl.z);
    RotateAboutX(&matrizModelView, DegreesToRadians(obj->anguloRot.x));
    RotateAboutY(&matrizModelView, DegreesToRadians(obj->anguloRot.y));
    RotateAboutZ(&matrizModelView, DegreesToRadians(obj->anguloRot.z));
    /* Diminuir o tamanho do modelo para nao sair fora do view volume */
    Scale(&matrizModelView, obj->factorEsc.x, obj->factorEsc.y, obj->factorEsc.z);
    /* Matriz de projeccao */
    glUniformMatrix4fv(uniform_matriz_proj, 1, GL_FALSE, matrizProj.m);
    /* Matriz de transformacao */
    glUniformMatrix4fv(uniform_matriz_model_view, 1, GL_FALSE, matrizModelView.m);
    /* Phong Illumination Model */
    /* Compute the 3 components: AMBIENT, DIFFUSE and SPECULAR */
    /* INITIALIZE THE 3 COMPONENTS WITH THE CONSTANT FACTORS */
    /* AMBIENT ILLUMINATION IS CONSTANT */
    for (i = 0; i < 3; i++)
    {
        ambientTerm[i] = obj->kAmb[i] * lights->intensidadeLuzAmbiente[i]; /* TESTING */
        diffuseTerm[i] = obj->kDif[i] * lights->intensidadeFLuz[i];
        specularTerm[i] = obj->kEsp[i] * lights->intensidadeFLuz[i];
    }
    /* SMOOTH-SHADING */
    /* Compute the illumination RGB value for every triangle vertex */
    /* Store the RGB values in the color array */
    indexArrayCores = 0;
    GLfloat normalDifuse = 0;
    GLfloat normalSpecular = 0;
    for (indexArrayVertices = 0; indexArrayVertices < (3 * obj->numVertices); indexArrayVertices += 3)
    {
        /* For every vertex */
        /* Get the XYZ coordinates and the normal vector */
        for (i = 0; i < 3; i++)
        {
            auxP[i] = obj->arrayVertices[ indexArrayVertices + i ];
            auxN[i] = obj->arrayNormais[ indexArrayVertices + i ];
        }
        /* The 4th homogeneous coordinate */
        auxP[3] = 1.0;
        auxN[3] = 0.0;
        /* Apply the global transformation matrix to each vertex */
        pontoP = multiplyPointByMatrix(&matrizModelView, auxP);
        /* And to the corresponding normal vector */
        vectorN = multiplyVectorByMatrix(&matrizModelView, auxN);
        /* Get the corresponding unit normal vector */
        convertToUnitVector(vectorN);
        /* DIFFUSE REFLECTION */
        /* Compute the vector L */
        for (i = 0; i < 3; i++)
        {
            vectorL[i] = lights->posicaoFLuz[i];
        }
        /* TWO SITUATIONS : POINT light source versus DIRECTIONAL light source */
        /* Get the corresponding unit vector */
        convertToUnitVector(vectorL);
        /* Compute cos (N . L) */
        cosNL = computeScalarProduct(vectorN, vectorL);
        // STOP and CHECK if you get the expected results
        /* SPECULAR REFLECTION */
        /* Compute the vector V --- The viewer is at (0,0,0) */
        vectorV = computeSymmetricVector(pontoP);
        /* Compute the HALFWAY VECTOR */
        vectorH = addVector(vectorL, vectorV);
        /* Get the corresponding unit vector */
        convertToUnitVector(vectorH);
        /* Compute cos (N . H) */
        cosNH = computeScalarProduct(vectorN, vectorH);
        /* STOP and CHECK if you get the expected results */
        /* ADD UP the 3 illumination components */
        /* AVOID RGB values greater the 1.0 */
        /* ONLY the AMBIENT component is being used at this moment... */

        obj->arrayCores[indexArrayCores] = ambientTerm[0] + diffuseTerm[0] * cosNL + specularTerm[0] * pow(cosNH, obj->coefPhong);
        indexArrayCores++;
        obj->arrayCores[indexArrayCores] = ambientTerm[1] + diffuseTerm[1] * cosNL + specularTerm[1] * pow(cosNH, obj->coefPhong);
        indexArrayCores++;
        obj->arrayCores[indexArrayCores] = ambientTerm[2] + diffuseTerm[2] * cosNL + specularTerm[2] * pow(cosNH, obj->coefPhong);
        indexArrayCores++;
        /* Libertar os arrays temporarios */
        free(pontoP);
        free(vectorN);
        free(vectorV);
        free(vectorH);
    }
    /* Push each element to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices);
    glDisableVertexAttribArray(attribute_coord3d);
    glDisableVertexAttribArray(attribute_corRGB);
}
void myDisplay(void)
{
    /* Limpar a janela */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* SHADERS */
    glUseProgram(programaGLSL);
    /* Input para o Vertex-Shader */
    for (int modelId = 0; modelId < pieceModels.size(); modelId++)
    {
        GraphicModelChess *obj = &pieceModels[modelId];
        
        Point2D<float> nPos = GraphicModelChess::convertChessPos(chess->getPosition(obj->piece));
        obj->desl.x = nPos.x;
        obj->desl.y = nPos.y;

        produceModelsShading(obj);
    }
    for (int modelId = 0; modelId < secondaryModels.size(); modelId++)
    {
        GraphicModelChess *obj = &secondaryModels[modelId];
        produceModelsShading(obj);
    }
    /* Display the result */
    /* DOUBLE-BUFFERING */
    glutSwapBuffers();
}


void myKeyboard(unsigned char key, int x, int y)
{
    /* Usar as teclas Q ou ESC para terminar o programa */
    int i;
    GraphicModelChess *obj;
    vector<Point2D<int> > pp;
    /*if (selectedModel != -1)
        obj = &pieceModels[selectedModel];
    else
        return;
    */
    switch (key)
    {
    case 'Q' :
    case 'q' :
    case 27  :  exit(EXIT_SUCCESS);
    case '+' :
        selectedModel++;
        printf("%d\n", selectedModel);
        glutPostRedisplay();
        break;
    case '-' :
        selectedModel--;
        printf("%d\n", selectedModel);
        glutPostRedisplay();
        break;
    case 't':
    case 'T':

        break;

    case 'Y':
    case 'y':

        //glutPostRedisplay();
        break;
    case 'p':
    case 'P':
        obj = &pieceModels[selectedModel];
        cout << chess->getCurrentPlayer() << ", player: " << obj->piece->player << endl;
        cout << obj->piece->getType() << endl;
        pp = chess->getPossiblePositions(obj->piece);
        for (vector<Point2D<int> >::iterator it = pp.begin(); it != pp.end(); ++it)
            cout << it->x << "," << it->y << " | ";

        cout << endl << *chess;
        break;
    case 'm':
    case 'M':
        obj = &pieceModels[selectedModel];
        pp = chess->getPossiblePositions(obj->piece);
        if (pp.size() != 0)
        {
            if (chess->move(obj->piece, pp[0]))
                glutTimerFunc(1000, myAnimationTimer, 0);
        }
        glutPostRedisplay();
    }
}


void mySpecialKeys(int key, int x, int y)
{
    /* Usar as teclas de cursor para controlar as rotacoes */
    GraphicModelChess *obj = &secondaryModels[0];
    switch (key)
    {
    case GLUT_KEY_LEFT :
        obj->desl.y -= 0.25;
        printf("%f %f\n", obj->desl.x, obj->desl.y);
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT :
        obj->desl.y += 0.25;
        printf("%f %f\n", obj->desl.x, obj->desl.y);
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP :
        obj->desl.x -= 0.25;
        printf("%f %f\n", obj->desl.x, obj->desl.y);
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN :
        obj->desl.x += 0.25;
        printf("%f %f\n", obj->desl.x, obj->desl.y);
        glutPostRedisplay();
        break;
    }
}



void onMouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN)
        return;
    /* int window_width = glutGet(GLUT_WINDOW_WIDTH);
     int window_height = glutGet(GLUT_WINDOW_HEIGHT);
     double x1 = 2 * (double) x / (double) window_width - 1;
     double y2 = -2 * (double) y / (double) window_height +1;

     GLint viewport[4];
     glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info
     float viewp[4];
     for (int i = 0; i < 4; i++)
         viewp[i] = viewport[i];

     multiplyVectorByMatrix(&matrizProj, viewp);
     */ /*Matrix4 viewProjectionInverse = inverse(projectionMatrix *
          viewMatrix);

     Point3D point3D = new Point3D(x, y, 0);
     return viewProjectionInverse.multiply(point3D);
     */


    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    GLbyte color[4];
    GLfloat depth;
    GLuint index;

    //glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    //glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    //glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    //printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
    //       x, y, color[0], color[1], color[2], color[3], depth, index);

    GLint viewport[4]; //var to hold the viewport info
    GLdouble modelview[16]; //var to hold the modelview info
    GLdouble projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates



    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    //glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    //winX = (float)x;
    //winY = (float)viewport[3] - (float)y;
    //winZ = 0;

    //get the world coordinates from the screen coordinates
    for (int i = 0; i < 16; i++)
    {
        modelview[i] = matrizModelView.m[i];
        projection[i] = matrizProj.m[i];
    }
    for (int i = 0; i < 4; i++)
        cout << viewport[i] << ", ";
    cout << endl;
    //gluUnProject(x, y, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    gluUnProject(x, window_height - y - 1, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ);

    //Point2D<float> pf = GraphicModelChess::convertBackToChessPos(worldX, worldY);
    printf("x: %f, y: %f, z: %f\n",
           worldX, worldY, worldZ);
}

void myAnimationTimer(int value)
{
    RotateAboutZ(&matrizProj, DegreesToRadians(20));
    glutPostRedisplay();
    if (value + 20 < 180)
        glutTimerFunc(250, myAnimationTimer, value + 20);
}

void registarCallbackFunctions(void)
{
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeys);
    glutMouseFunc(onMouse);
}
