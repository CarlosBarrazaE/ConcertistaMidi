#include "figura.h++"

unsigned int Figura::Ultimo_indice_seleccionado = 0;

Figura::Figura(Sombreador *sombreador)
{
	this->m_sombreador = sombreador;
}

Figura::~Figura()
{
}
