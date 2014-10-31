HEADERS		= 	callbacks.hpp consoleIO.hpp init.hpp menus.hpp GraphicalModelChess.hpp globals.hpp \ 
				chess-engine/Chess.hpp chess-engine/ChessPiece.hpp \
				chess-engine/Pieces/Pawn.hpp chess-engine/Pieces/Knight.hpp chess-engine/Pieces/Bishop.hpp \
				chess-engine/Pieces/Tower.hpp chess-engine/Pieces/King.hpp chess-engine/Pieces/Queen.hpp \
				utils/mathUtils.hpp utils/Points.hpp shaders/shaders.hpp LightModel.hpp
				
SOURCES		=	project60337.cpp globals.cpp callbacks.cpp consoleIO.cpp init.cpp menus.cpp models.cpp \
				shaders/shaders.cpp chess-engine/ChessPiece.cpp chess-engine/Chess.cpp \
				chess-engine/Pieces/Pawn.cpp chess-engine/Pieces/Knight.cpp chess-engine/Pieces/Bishop.cpp \
				chess-engine/Pieces/Tower.cpp chess-engine/Pieces/King.cpp chess-engine/Pieces/Queen.cpp \
				utils/mathUtils.cpp LightModel.cpp

INCLUDEPATH     = 
LIBS            += -lGLEW -lglut -lGL -lX11  -lm 
TARGET			= chess
CONFIG 			-= qt warn_on

QMAKE_CXXFLAGS_WARN_ON -= -Wall -W -W1, -01 -m64
QMAKE_CXXFLAGS_RELEASE =
QMAKE_CXXFLAGS_PRECOMPILE  =
QMAKE_CXXFLAGS_USE_PRECOMPILE =
QMAKE_CXXFLAGS =
QMAKE_CXXFLAGS_DEPS =

QMAKE_CFLAGS_WARN_ON -= -Wall -W -W1, -01 -m64
QMAKE_CFLAGS_RELEASE = 
QMAKE_CFLAGS_PRECOMPILE  =
QMAKE_CFLAGS_USE_PRECOMPILE =
QMAKE_CFLAGS =
QMAKE_CFLAGS_DEPS =