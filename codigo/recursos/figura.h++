#ifndef FIGURA_H
#define FIGURA_H

#include "sombreador.h++"

class Figura
{
protected:
	unsigned int m_indice_figura;
	Sombreador *m_sombreador;

	static unsigned int Ultimo_indice_seleccionado;
public:
	Figura(Sombreador *sombreador);
	~Figura();

	void seleccionar_figura();
};

#endif
