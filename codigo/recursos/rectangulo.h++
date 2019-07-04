#ifndef RECTANGULO_H
#define RECTANGULO_H

#include <glm/glm.hpp>

#include "figura.h++"
#include "textura_2d.h++"
#include "color.h++"

class Rectangulo : public Figura
{
private:
	void inicializar();

	Color color_rectangulo;
	bool textura_activada;
public:
	Rectangulo(Sombreador *sombreador);
	~Rectangulo();

	void color(Color color);
	void textura(bool estado);

	void dibujar(float x, float y, float ancho, float alto, Color color, bool textura);
	void dibujar(float x, float y, float ancho, float alto, Color color);
	void dibujar(float x, float y, float ancho, float alto);
};

#endif
