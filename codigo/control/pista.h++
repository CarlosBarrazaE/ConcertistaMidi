#ifndef PISTA_H
#define PISTA_H

#include "../recursos/color.h++"

#define NUMERO_COLORES_PISTA 9

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
	static Color colores_pista[NUMERO_COLORES_PISTA];
	Pista(Color color, Modo modo);
	~Pista();

	Color o_color();
	Modo o_modo();
};

#endif
