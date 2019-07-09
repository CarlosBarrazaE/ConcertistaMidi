#ifndef PARTICULA_H
#define PARTICULA_H

#include "color.h++"

struct Particula
{
	float posicion_x, posicion_y;
	float velocidad_x, velocidad_y;
	Color color;
	float vida;

	Particula();
};

#endif
