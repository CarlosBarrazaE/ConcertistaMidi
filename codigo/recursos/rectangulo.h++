#ifndef RECTANGULO_H
#define RECTANGULO_H

#include <glm/glm.hpp>

#include "figura.h++"
#include "sombreador.h++"
#include "textura_2d.h++"
#include "color.h++"

class Rectangulo : public Figura
{
private:
	void inicializar();

	Color color;
	Textura2D *textura;
	bool tiene_textura;
public:
	Rectangulo(Sombreador *sombreador, Color color);
	Rectangulo(Sombreador *sombreador, Textura2D *textura);
	Rectangulo(Sombreador *sombreador, Textura2D *textura, Color color);
	~Rectangulo();

	void dibujar_rectangulo(float x, float y, float ancho, float alto);
	void dibujar_rectangulo(float x, float y, float ancho, float alto, Color color);
};

#endif
