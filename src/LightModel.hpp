/*
 * LightModel.hpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#ifndef LIGHTMODEL_H
#define LIGHTMODEL_H

#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include "utils/mathUtils.hpp"
#include "utils/Points.hpp"

class LightModel {
public:
	LightModel();
	LightModel(float[], float[], float[]);
	~LightModel();

	float intensidadeFLuz[4];
	float posicaoFLuz[4];
	float intensidadeLuzAmbiente[4];
};

#endif