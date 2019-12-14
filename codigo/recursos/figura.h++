#ifndef FIGURA_H
#define FIGURA_H

#include "sombreador.h++"

class Figura
{
protected:
	static unsigned int Ultimo_indice_seleccionado;
	unsigned int indice_figura;
	Sombreador *sombreador;
public:
	Figura(Sombreador *sombreador);
	~Figura();
};

#endif
