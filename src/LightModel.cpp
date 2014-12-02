/*
 * LightModel.cpp
 *
 * Author: Diogo Silva (dbtds@ua.pt)
 *
 */

#include "LightModel.hpp"

using namespace std;

LightModel::LightModel() {
	float intensidadeFLuz[] = {0, 0, 0, 0};
	float posicaoFLuz[] = {0, 0, 0, 0};
	float intensidadeLuzAmbiente[] = {0, 0, 0, 0};

	copy(intensidadeFLuz, intensidadeFLuz + 4, this->intensidadeFLuz);
	copy(posicaoFLuz, posicaoFLuz + 4, this->posicaoFLuz);
	copy(intensidadeLuzAmbiente, intensidadeLuzAmbiente + 4, this->intensidadeLuzAmbiente);
}

LightModel::LightModel(float intensidadeFLuz[], float posicaoFLuz[], float intensidadeLuzAmbiente[]) {
	copy(intensidadeFLuz, intensidadeFLuz + 4, this->intensidadeFLuz);
	copy(posicaoFLuz, posicaoFLuz + 4, this->posicaoFLuz);
	copy(intensidadeLuzAmbiente, intensidadeLuzAmbiente + 4, this->intensidadeLuzAmbiente);
}

LightModel::~LightModel() {
	
}