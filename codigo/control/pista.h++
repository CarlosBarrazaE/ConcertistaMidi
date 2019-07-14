#ifndef PISTA_H
#define PISTA_H

#include "../recursos/color.h++"

enum Modo
{
	Tocar,
	Automatico,
	NoTocar,
	AutomaticoOculto,
};

class Pista
{
private:
	Color color_pista;
	Modo modo_pista;
public:
	Pista(Color color, Modo modo);
	~Pista();
	Color o_color();
	Modo o_modo();
};

#endif
