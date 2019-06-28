#include "pista.h++"

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
