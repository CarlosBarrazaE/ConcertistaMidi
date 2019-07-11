#ifndef RECTANGULO_H
#define RECTANGULO_H

#include <glm/glm.hpp>

#include "figura.h++"
#include "textura_2d.h++"
#include "color.h++"

class Rectangulo : public Figura
{
private:
	unsigned int indice_objeto;
	Color color_rectangulo;
	bool textura_activada;
	bool textura_estirable_horizontal;
	bool textura_estirable_vertical;
	float borde_horizontal;//Entre 0 y 1
	float borde_vertical;//Entre 0 y 1
public:
	Rectangulo(Sombreador *sombreador);
	~Rectangulo();

	void color(Color color);
	void textura(bool estado);
	void extremos_fijos(bool horizontal, bool vertical);

	void dibujar(float x, float y, float ancho, float alto, Color color);
	void dibujar(float x, float y, float ancho, float alto);

	void dibujar_estirable(float x, float y, float ancho, float alto, float borde_horizontal, float borde_vertical);
};

#endif
