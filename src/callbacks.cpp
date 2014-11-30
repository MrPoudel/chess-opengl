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
void animation_rotateProjRight(int value);
void animation_rotateProjLeft(int value);
void createRotateProjectionAnimation(void);
void makeChessMove(GraphicModelChess*, vector<Point2D<int> >);

void produceModelsShading(GraphicModelChess *obj)
{
    glEnableVertexAttribArray(attribute_coord3d);
    glEnableVertexAttribArray(attribute_normal3d);
    glEnableVertexAttribArray(attribute_texcoord);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj->textureID);
    GLfloat ambientTerm[3];
    GLfloat diffuseTerm[3];
    GLfloat specularTerm[3];
    /* Caracteristicas do array de coordenadas */
    float *coordenadas = new GLfloat[obj->arrayVertices.size() * sizeof(GLfloat)];
    float *normais = new GLfloat[obj->arrayNormais.size() * sizeof(GLfloat)];

    glVertexAttribPointer(attribute_coord3d,        // attribute
                          3,                        // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,                 // the type of each element
                          GL_FALSE,                 // take our values as-is
                          0,                        // no extra data between each position
                          obj->arrayVertices.data());      // pointer to the C array

    glVertexAttribPointer(attribute_normal3d,       // attribute
                          3,                        // number of elements per vertex, here (R,G,B)
                          GL_FLOAT,                 // the type of each element
                          GL_FALSE,                 // take our values as-is
                          0,                        // no extra data between each position
                          obj->arrayNormais.data());       // pointer to the C array
    
    glVertexAttribPointer(attribute_texcoord, // attribute
                          2,                  // number of elements per vertex, here (x,y)
                          GL_FLOAT,           // the type of each element
                          GL_FALSE,           // take our values as-is
                          0,                  // no extra data between each position
                          obj->arrayTextures.data());

    matrizModelView = IDENTITY_MATRIX;
    Translate(&matrizModelView, obj->desl.x, obj->desl.y, obj->desl.z);
    RotateAboutX(&matrizModelView, DegreesToRadians(obj->anguloRot.x));
    RotateAboutY(&matrizModelView, DegreesToRadians(obj->anguloRot.y));
    RotateAboutZ(&matrizModelView, DegreesToRadians(obj->anguloRot.z));
    /* Diminuir o tamanho do modelo para nao sair fora do view volume */
    Scale(&matrizModelView, obj->factorEsc.x, obj->factorEsc.y, obj->factorEsc.z);
    /* Matriz de projeccao e Matriz de transformacao */
    glUniformMatrix4fv(glGetUniformLocation(programaGLSL, "matrizProj"), 1, GL_FALSE, matrizProj.m);
    glUniformMatrix4fv(glGetUniformLocation(programaGLSL, "matrizModelView"), 1, GL_FALSE, matrizModelView.m);

    for (int i = 0; i < 3; i++)
    {
        ambientTerm[i] = obj->kAmb[i] * lights->intensidadeLuzAmbiente[i];
        diffuseTerm[i] = obj->kDif[i] * lights->intensidadeFLuz[i];
        specularTerm[i] = obj->kEsp[i] * lights->intensidadeFLuz[i];
    }

    glUniform4fv(glGetUniformLocation(programaGLSL, "ambientTerm"), 1, ambientTerm);
    glUniform4fv(glGetUniformLocation(programaGLSL, "diffuseTerm"), 1, diffuseTerm);
    glUniform4fv(glGetUniformLocation(programaGLSL, "specularTerm"), 1, specularTerm);
    glUniform4fv(glGetUniformLocation(programaGLSL, "posicaoFLuz"), 1, lights->posicaoFLuz);
    glUniform1f(glGetUniformLocation(programaGLSL, "coefPhong"), obj->coefPhong);
    glUniform1i(glGetUniformLocation(programaGLSL, "mytexture"), /*GL_TEXTURE*/0);

    glDrawArrays(GL_TRIANGLES, 0, obj->numVertices);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(attribute_coord3d);
    glDisableVertexAttribArray(attribute_normal3d);
    glDisableVertexAttribArray(attribute_texcoord);

    delete[] coordenadas;
    delete[] normais;
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programaGLSL);
    /* Chess pieces */
    /* [0-15] - Player 1 */ 
    /* [16-31] - Player 2 */
    for (int modelId = 0; modelId < pieceModels.size(); modelId++)
    {
        GraphicModelChess *obj = &pieceModels[modelId];

        Point2D<float> nPos = GraphicModelChess::convertChessPos(chess->getCompletePosition(obj->piece));
        obj->desl.x = nPos.x;
        obj->desl.y = nPos.y;
        produceModelsShading(obj);
    }
    /* Secondary models includes only chess table atm */
    produceModelsShading(chessTable);
    produceModelsShading(skybox);
    if (selectedFrame != NULL)
        produceModelsShading(selectedFrame);

    for (int modelId = 0; modelId < previewPositions.size(); modelId++)
        produceModelsShading(previewPositions[modelId]);
    glutSwapBuffers();
}

void refreshPreviewPanels()
{
    while (!previewPositions.empty()) {
        delete previewPositions.back();
        previewPositions.pop_back();
    }

    vector<Point2D<int> > pp = chess->getPossiblePositions(pieceModels[selectedModel].piece);
    previewPositions.push_back(GraphicModelChess::generatePreviewSquare(
                                   GraphicModelChess::convertChessPos(
                                       chess->getBoardPosition(pieceModels[selectedModel].piece)
                                   ), 1, 1, 0, 0.9, 0.02)
                              );
    for (vector<Point2D<int> >::iterator it = pp.begin(); it != pp.end(); ++it)
    {
        if (!chess->isFieldEmpty(*it))
            previewPositions.push_back(GraphicModelChess::generatePreviewSquare(
                                           GraphicModelChess::convertChessPos(*it), 1, 0, 0, 0.9, 0.02)
                                      );
        else
            previewPositions.push_back(GraphicModelChess::generatePreviewSquare(
                                           GraphicModelChess::convertChessPos(*it), 0, 1, 0, 0.9, 0.02)
                                      );
    }
}

void refreshSelectedPosition() {
    if (selectedPosition == -1) {
        delete selectedFrame;
        selectedFrame = NULL;
    } else {
        Point2D<int> vec = chess->getPossiblePositions(pieceModels[selectedModel].piece)[selectedPosition];
        selectedFrame = GraphicModelChess::generatePreviewSquare(
                                            GraphicModelChess::convertChessPos(vec), 0, 1, 1, 0.8, 0.03
                                          );
    }
}

void myKeyboard(unsigned char key, int x, int y)
{
    int i;
    GraphicModelChess *obj;
    vector<Point2D<int> > pp;

    bool changed;
    switch (key)
    {
    case 'Q' :
    case 'q' :
    case 27  :  exit(EXIT_SUCCESS);
    case '+' :
        if ((chess->getCurrentPlayer() == ONE && selectedModel < 15) || 
            (chess->getCurrentPlayer() == TWO && selectedModel < 31)) 
        {
            selectedModel++;
            selectedPosition = -1;
            refreshPreviewPanels();
            refreshSelectedPosition();
            glutPostRedisplay();
        }
        break;
    case '-' :
        if ((chess->getCurrentPlayer() == ONE && selectedModel > 0) || 
            (chess->getCurrentPlayer() == TWO && selectedModel > 16)) 
        {
            selectedModel--;
            selectedPosition = -1;
            refreshPreviewPanels();
            refreshSelectedPosition();
            glutPostRedisplay();
        }
        break;
    case '.':
        obj = &pieceModels[selectedModel];
        pp = chess->getPossiblePositions(obj->piece);
        if (pp.size() != 0) {
            selectedPosition = (selectedPosition + 1) % pp.size();
            refreshSelectedPosition();
            glutPostRedisplay();
        }
        break;
    case ',':
        obj = &pieceModels[selectedModel];
        pp = chess->getPossiblePositions(obj->piece);
        if (pp.size() != 0) {
            selectedPosition = (selectedPosition - 1) % pp.size();
            refreshSelectedPosition();
            glutPostRedisplay();
        }
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
        if (selectedPosition < pp.size() && selectedPosition >= 0) {
            makeChessMove(obj, pp);
        }
        
    }
}

void mySpecialKeys(int key, int x, int y)
{
    if (animationActive)
        return;
    
    GraphicModelChess *obj = chessTable;
    switch (key)
    {
    case GLUT_KEY_LEFT :
        tableRotation.z += 2;
        RotateAboutZ(&matrizProj, DegreesToRadians(2));
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT :
        tableRotation.z -= 2;
        RotateAboutZ(&matrizProj, DegreesToRadians(-2));
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP :
        tableRotation.y -= 2;
        
        RotateAboutZ(&matrizProj, DegreesToRadians(-tableRotation.z));
        RotateAboutY(&matrizProj, DegreesToRadians(-2));
        RotateAboutZ(&matrizProj, DegreesToRadians(tableRotation.z));
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN :
        tableRotation.y += 2;
        
        RotateAboutZ(&matrizProj, DegreesToRadians(-tableRotation.z));
        RotateAboutY(&matrizProj, DegreesToRadians(2));
        RotateAboutZ(&matrizProj, DegreesToRadians(tableRotation.z));
        glutPostRedisplay();
        break;
    }
}

void onMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !animationActive)
        last.x = curr.x = x;
        last.y = curr.y = y;
    
    if (state != GLUT_DOWN)
        return;
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    for (int i = 0; i < 16; i++) 
        projection[i] = matrizProj.m[i];
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);


    Point2D<float> p = GraphicModelChess::convertBackToChessPos(posX, posY);
    Point2D<int> np;
    np.x = rint(p.x);
    np.y = rint(p.y);

    if (np.x >= 0 && np.x < 8 && np.y >= 0 && np.y < 8) {
        /* Find proper model */
        int tmpSelectedModel = -1, tmpSelectedPos = -1;
        for (int i = 0; i < 32; i++) {
            Point2D<int> tmp = chess->getBoardPosition(pieceModels[i].piece);
            if (tmp.x == np.y && tmp.y == np.x) {
                tmpSelectedModel = i;
                break;
            }
        }

        vector<Point2D<int> > possiblePos = chess->getPossiblePositions(pieceModels[selectedModel].piece);
        if (selectedModel >= 0 && selectedModel <= 31) {
            for (int i = 0; i < possiblePos.size(); i++) {
                if (np.x == possiblePos[i].y && np.y == possiblePos[i].x) {
                    tmpSelectedPos = i;
                    break;
                }
            }
        }
        if (tmpSelectedPos == -1 && tmpSelectedModel != -1 && 
            pieceModels[tmpSelectedModel].piece->player != chess->getCurrentPlayer())
            return;

        if (selectedPosition == tmpSelectedPos && selectedPosition != -1) {
            makeChessMove(&pieceModels[selectedModel], possiblePos);
        } else if (tmpSelectedPos != -1) {
            selectedPosition = tmpSelectedPos;
            refreshSelectedPosition();
            glutPostRedisplay();
        } else if (tmpSelectedModel != -1) {
            selectedModel = tmpSelectedModel;
            selectedPosition = -1;
            refreshPreviewPanels();
            refreshSelectedPosition();
            glutPostRedisplay();
        }
    }
}

void onDrag(int x, int y)
{
    if (animationActive)
        return;

    last.x = curr.x;
    last.y = curr.y;
    curr.x = x;
    curr.y = y;

    if (curr.x == -1 && curr.y == -1)
        return;

    float rotatez = (float)(last.x - curr.x) * 0.15;
    float rotatey = (float)(last.y - curr.y) * 0.15;
    
    tableRotation.z += rotatez;
    cout << tableRotation.z << endl;
    RotateAboutZ(&matrizProj, DegreesToRadians(rotatez));

    RotateAboutZ(&matrizProj, DegreesToRadians(-tableRotation.z));
    RotateAboutY(&matrizProj, DegreesToRadians(rotatey));
    RotateAboutZ(&matrizProj, DegreesToRadians(tableRotation.z));

    glutPostRedisplay();
    
}

void makeChessMove(GraphicModelChess * obj, vector<Point2D<int> > possiblePos) {
    if (chess->move(obj->piece, possiblePos[selectedPosition])) {
        if (!chess->isGameFinished()) {
            createRotateProjectionAnimation();
            for (int i = 0; i < pieceModels.size(); i++) {
                if (pieceModels[i].piece->player == chess->getCurrentPlayer() && pieceModels[i].piece->getType() == "King") {
                    selectedModel = i;
                    break;
                }
            }
            selectedPosition = -1;
            refreshSelectedPosition();
        }
        refreshPreviewPanels();
        glutPostRedisplay();
    }
}


void createRotateProjectionAnimation() {
    int turnAngle = (int) tableRotation.z % 360;
    int realRotation;
    if (chess->getCurrentPlayer() == ONE)
        turnAngle += 180;
        
    if (turnAngle > 180) {
        realRotation = -turnAngle + 180;
        glutTimerFunc(500, animation_rotateProjRight, turnAngle - 360);
    } else if (turnAngle < -180) {
        realRotation = -turnAngle - 180;
        glutTimerFunc(500, animation_rotateProjLeft, 360 + turnAngle);
    } else if (turnAngle >= 0) {
        realRotation = 180 - turnAngle;
        glutTimerFunc(500, animation_rotateProjLeft, turnAngle);
    } else {
        realRotation = -turnAngle -180;
        glutTimerFunc(500, animation_rotateProjRight, turnAngle);
    }

    tableRotation.z += realRotation;
}
void animation_rotateProjLeft(int value) {
    animationActive = true;
    RotateAboutZ(&matrizProj, DegreesToRadians(1));
    glutPostRedisplay();
    if (abs(value) + 1 < 180) 
        glutTimerFunc(5, animation_rotateProjLeft, value + 1);
    else
        animationActive = false;
}

void animation_rotateProjRight(int value) {
    animationActive = true;
    RotateAboutZ(&matrizProj, DegreesToRadians(-1));
    glutPostRedisplay();
    if (abs(value) + 1 < 180)
        glutTimerFunc(5, animation_rotateProjRight, value - 1);
    else
        animationActive = false;
}

void registarCallbackFunctions(void)
{
    refreshPreviewPanels();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeys);
    glutMouseFunc(onMouse);
    glutMotionFunc(onDrag);
}
