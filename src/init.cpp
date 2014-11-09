/*
 * init.c
 *
 * Ficheiro de implementacao do modulo INIT.
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define GLEW_STATIC /* Necessario se houver problemas com a lib */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "globals.hpp"
#include "utils/mathUtils.hpp"
#include "models.hpp"

void inicializarEstado(void)
{
    /* DOUBLE-BUFFERING + DEPTH-TESTING */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    /* Definir a cor do fundo */
    glClearColor(1, 1, 1, 1.0);
    /* Atributos das primitivas */
    glPointSize(4.0);
    glLineWidth(3.0);
    /* Modo de desenho dos poligonos */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    /* Back-Face Culling */
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Matriz de projeccao � inicialmente a IDENTIDADE => Proj. Paralela Ortogonal */
    matrizProj = IDENTITY_MATRIX;
    matrizModelView = IDENTITY_MATRIX;

    chess = new Chess();
    selectedModel = 0;
    selectedPosition = -1;
}


void inicializarJanela(void)
{
    /* Caracteristicas da janela de saida */
    glutInitWindowSize(700, 700);   /* Usar variaveis GLOBAIS para estes parametros */
    glutInitWindowPosition(300, 20);
    /* Para terminar de modo apropriado */
    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );
    /* Criar a janela de saida */
    windowHandle = glutCreateWindow("Chess 2014 OpenGL");
    if (windowHandle < 1)
    {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }
}

void inicializarPlanoProjeccao(void)
{
    proj.fovy = 60;
    proj.aspect_ratio = 1;
    proj.near_plane = 1;
    proj.far_plane = 50;
}
void inicializarFontesDeLuz(void)
{
    /* Intensidade Luminosa */
    // IL
    float intensidadeFLuz_0[4];
    intensidadeFLuz_0[0] = 0.5;
    intensidadeFLuz_0[1] = 0.5;
    intensidadeFLuz_0[2] = 0.5;
    intensidadeFLuz_0[3] = 1.0;
    /* Posicao */
    float posicaoFLuz_0[4];
    posicaoFLuz_0[0] = 0.0;
    posicaoFLuz_0[1] = 0.0;
    posicaoFLuz_0[2] = 4.0;
    posicaoFLuz_0[3] = 1.0;
    /* Luz Ambiente */
    // IA
    float intensidadeLuzAmbiente[4];
    intensidadeLuzAmbiente[0] = 0.2;
    intensidadeLuzAmbiente[1] = 0.2;
    intensidadeLuzAmbiente[2] = 0.2;
    intensidadeLuzAmbiente[3] = 1.0;

    lights = new LightModel(intensidadeFLuz_0, posicaoFLuz_0, intensidadeLuzAmbiente);
}

void inicializarModelos(void)
{
    vector<ChessPiece *> list = chess->getListPieces();
    GraphicModelChess obj;
    for (vector<ChessPiece *>::iterator it = list.begin(); it != list.end(); ++it)
    {
        obj = GraphicModelChess();
        obj.piece = *it;
        if (obj.piece->getType() == "Queen")
            lerVerticesDeFicheiro(projectPath + "models/queen.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        else if (obj.piece->getType() == "Bishop")
            lerVerticesDeFicheiro(projectPath + "models/bishop.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        else if (obj.piece->getType() == "Pawn")
            lerVerticesDeFicheiro(projectPath + "models/pawn.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        else if (obj.piece->getType() == "King")
            lerVerticesDeFicheiro(projectPath + "models/king.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        else if (obj.piece->getType() == "Knight")
            lerVerticesDeFicheiro(projectPath + "models/knight.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        else if (obj.piece->getType() == "Tower")
            lerVerticesDeFicheiro(projectPath + "models/tower.obj", &obj.numVertices, &obj.arrayVertices, &obj.arrayNormais);
        /* Propriedades do material */
        if (obj.piece->player == ONE)
        {
            obj.kAmb[0] = 0.8;
            obj.kAmb[1] = 0.8;
            obj.kAmb[2] = 0.8;
            obj.kAmb[3] = 1.0;

            obj.kDif[0] = 0.9;
            obj.kDif[1] = 0.9;
            obj.kDif[2] = 0.9;
            obj.kDif[3] = 1.0;
        }
        else
        {
            obj.kAmb[0] = 0.1;
            obj.kAmb[1] = 0.1;
            obj.kAmb[2] = 0.1;
            obj.kAmb[3] = 1.0;

            obj.kDif[0] = 0.3;
            obj.kDif[1] = 0.3;
            obj.kDif[2] = 0.3;
            obj.kDif[3] = 1.0;
        }

        obj.kEsp[0] = 0.9;
        obj.kEsp[1] = 0.9;
        obj.kEsp[2] = 0.9;
        obj.kEsp[3] = 1.0;
        obj.coefPhong = 30;
        /* Parametros das transformacoes */
        Point2D<int> pos = chess->getPosition(obj.piece);
        // -0.35 -0.25 -0.15 -0.05 0.05 ..
        Point2D<float> nP = GraphicModelChess::convertChessPos(pos);
        obj.desl.x = nP.x;
        obj.desl.y = nP.y;
        obj.desl.z = 0;
        obj.anguloRot.x = 0;
        obj.anguloRot.y = 0;
        obj.anguloRot.z = obj.piece->player == ONE ? 180 : 0;
        obj.factorEsc.x = 1;
        obj.factorEsc.y = 1;
        obj.factorEsc.z = 1;

        pieceModels.push_back(obj);
    }

    /* Tabuleiro */
    chessTable = new GraphicModelChess();
    chessTable->piece = NULL;
    lerVerticesDeFicheiro(projectPath + "models/board.obj", &chessTable->numVertices, &chessTable->arrayVertices, &chessTable->arrayNormais);
    chessTable->kAmb[0] = 0.9;
    chessTable->kAmb[1] = 0.9;
    chessTable->kAmb[2] = 0.9;
    chessTable->kAmb[3] = 1.0;
    chessTable->kDif[0] = 0.9;
    chessTable->kDif[1] = 0.9;
    chessTable->kDif[2] = 0.9;
    chessTable->kDif[3] = 1.0;
    chessTable->kEsp[0] = 0.9;
    chessTable->kEsp[1] = 0.9;
    chessTable->kEsp[2] = 0.9;
    chessTable->kEsp[3] = 1.0;
    chessTable->coefPhong = 100;
    chessTable->desl.x = 0;
    chessTable->desl.y = 0;
    chessTable->desl.z = 0;
    chessTable->anguloRot.x = 0;
    chessTable->anguloRot.y = 0;
    chessTable->anguloRot.z = 0;
    chessTable->factorEsc.x = 1;
    chessTable->factorEsc.y = 1;
    chessTable->factorEsc.z = 1;

    matrizProj = CreateProjectionMatrix(proj.fovy, proj.aspect_ratio, proj.near_plane, proj.far_plane);
    /* Posicionar no interior do View Volome */
    Translate(&matrizProj, 0, 0, -6);
    // Possicionar meio inclinado
    RotateAboutX(&matrizProj, DegreesToRadians(-45));
    // Virar camera para o player 1
    RotateAboutZ(&matrizProj, DegreesToRadians(90));
}

void libertarArraysGlobais(void)
{
    delete lights;
    delete chess;
    for (int i = 0; i < pieceModels.size(); i++) {
        free(pieceModels[i].arrayVertices);
        free(pieceModels[i].arrayNormais);
    }
    for (int i = 0; i < previewPositions.size(); i++) {
        free(previewPositions[i].arrayNormais);
        free(previewPositions[i].arrayVertices);
    }
    free(chessTable->arrayVertices);
    free(chessTable->arrayNormais);
    delete chessTable;
    if (selectedFrame != NULL) {
        free(selectedFrame->arrayNormais);
        free(selectedFrame->arrayVertices);
        delete selectedFrame;
    }
}
