#include "pista.h++"

Color Pista::colores_pista[NUMERO_COLORES_PISTA] = {
	Color(0.0f, 0.598f, 0.0f),
	Color(0.0f, 0.598f, 1.0f),
	Color(1.0f, 0.598f, 1.0f),
	Color(1.0f, 0.424f, 0.0f),
	Color(0.0f, 0.761f, 0.467f),
	Color(0.0f, 0.8, 1.0f),
	Color(1.0f, 0.761f, 0.609f),
	Color(1.0f, 0.761f, 0.0f),
	Color(0.407f, 0.348f, 1.0f)
};

Pista::Pista(Color color, Modo modo)
{
	this->color_pista = color;
	this->modo_pista = modo;
}

Pista::~Pista()
{
}

Color Pista::o_color()
{
	return this->color_pista;
}

Modo Pista::o_modo()
{
	return this->modo_pista;
}
