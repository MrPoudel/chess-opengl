HEADERS		= callbacks.h consoleIO.h init.h mathUtils.h menus.h models.h shaders.h globals.h
SOURCES		= project60337.cpp globals.cpp callbacks.cpp consoleIO.cpp init.cpp mathUtils.cpp menus.cpp models.cpp shaders.cpp

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