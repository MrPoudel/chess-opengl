HEADERS		= callbacks.hpp consoleIO.hpp init.hpp mathUtils.hpp menus.hpp models.hpp shaders.hpp globals.hpp \ 
				chess-engine/Chess.hpp chess-engine/ChessPiece.hpp \
				chess-engine/Pieces/Pawn.hpp \
				Points.hpp
SOURCES		= project60337.cpp globals.cpp callbacks.cpp consoleIO.cpp init.cpp mathUtils.cpp menus.cpp models.cpp \
				shaders.cpp chess-engine/ChessPiece.cpp chess-engine/Chess.cpp chess-engine/Pieces/Pawn.cpp

INCLUDEPATH     = 
LIBS            += -lGLEW -lGL -lglut
TARGET			= chess
CONFIG -= qt warn_on

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