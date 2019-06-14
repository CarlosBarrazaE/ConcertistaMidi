#include "figura.h++"

unsigned int Figura::ultimo_indice_seleccionado = 0;

Figura::Figura(Sombreador *sombreador)
{
	this->sombreador = sombreador;
}

Figura::~Figura()
{
}
