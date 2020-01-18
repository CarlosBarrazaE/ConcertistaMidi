#ifndef FIGURA_H
#define FIGURA_H

#include "sombreador.h++"

class Figura
{
protected:
	unsigned int indice_figura;
	Sombreador *sombreador;
public:
    static unsigned int Ultimo_indice_seleccionado;
	Figura(Sombreador *sombreador);
	~Figura();
};

#endif
