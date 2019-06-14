#ifndef RECTANGULO_H
#define RECTANGULO_H

#include <glm/glm.hpp>

#include "figura.h++"
#include "sombreador.h++"

class Rectangulo : public Figura
{
public:
	Rectangulo(Sombreador *sombreador, bool textura);
	~Rectangulo();

	void dibujar_rectangulo(float x, float y, float ancho, float alto);
};

#endif
