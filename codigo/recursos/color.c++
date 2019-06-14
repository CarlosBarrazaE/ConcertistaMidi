#include "color.h++"

Color::Color()
{
	this->rojo = 0.0;
	this->verde = 0.0;
	this->azul = 0.0;
}

Color::Color(float rojo, float verde, float azul)
{
	if(rojo < 0)
		this->rojo = 0;
	else if(rojo > 1.0)
		this->rojo = 1.0;
	else
		this->rojo = rojo;

	if(verde < 0)
		this->verde = 0;
	else if(verde > 1.0)
		this->verde = 1.0;
	else
		this->verde = verde;

	if(azul < 0)
		this->azul = 0;
	else if(azul > 1.0)
		this->azul = 1.0;
	else
		this->azul = azul;
}

Color::Color(double rojo, double verde, double azul)
{
	if(rojo < 0)
		this->rojo = 0;
	else if(rojo > 1.0)
		this->rojo = 1.0;
	else
		this->rojo = rojo;

	if(verde < 0)
		this->verde = 0;
	else if(verde > 1.0)
		this->verde = 1.0;
	else
		this->verde = verde;

	if(azul < 0)
		this->azul = 0;
	else if(azul > 1.0)
		this->azul = 1.0;
	else
		this->azul = azul;
}

Color::Color(int rojo, int verde, int azul)
{
	if(rojo < 0)
		this->rojo = 0;
	else if(rojo > 254)
		this->rojo = 1.0;
	else
		this->rojo = rojo / 254.0;

	if(verde < 0)
		this->verde = 0;
	else if(verde > 254)
		this->verde = 1.0;
	else
		this->verde = verde / 254.0;

	if(azul < 0)
		this->azul = 0;
	else if(azul > 254)
		this->azul = 1.0;
	else
		this->azul = azul / 254.0;
}

Color::~Color()
{
}

float Color::o_rojo()
{
	return this->rojo;
}

float Color::o_verde()
{
	return this->verde;
}

float Color::o_azul()
{
	return this->azul;
}

bool Color::operator == (const Color &c) const
{
	return this->rojo == c.rojo && this->verde == c.verde && this->azul == c.azul;
}

bool Color::operator != (const Color &c) const
{
	return this->rojo != c.rojo || this->verde != c.verde || this->azul != c.azul;
}
