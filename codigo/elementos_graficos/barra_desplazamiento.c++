#include "barra_desplazamiento.h++"

Barra_Desplazamiento::Barra_Desplazamiento(int x, int y, int ancho, int alto, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->ancho_actual = 0;
	this->alto_actual = 0;
	this->desplazamiento_x = 0;
	this->desplazamiento_y = 0;
}

Barra_Desplazamiento::~Barra_Desplazamiento()
{
}

void Barra_Desplazamiento::agregar_elemento(Elemento *e)
{
	elementos.push_back(e);
}

void Barra_Desplazamiento::actualizar(unsigned int diferencia_tiempo)
{
	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->actualizar(diferencia_tiempo);
	}
}

void Barra_Desplazamiento::dibujar()
{
	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->dibujar();
	}
}

void Barra_Desplazamiento::evento_raton(Raton *raton)
{
	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->evento_raton(raton);
	}
}
