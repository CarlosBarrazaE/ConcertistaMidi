#include "raton.h++"

Raton::Raton()
{
	this->posicion_x = 0;
	this->posicion_y = 0;
	this->desplazamiento_y = 0;
	this->boton_izquierdo = false;
	this->boton_central = false;
	this->boton_derecho = false;
}

void Raton::actualizar_boton(BotonRaton boton, bool estado)
{
	if(boton == BotonIzquierdo)
		this->boton_izquierdo = estado;
	else if(boton == BotonCentral)
		this->boton_central = estado;
	else if(boton == BotonDerecho)
		this->boton_derecho = estado;

	this->desplazamiento_y = 0;
}

void Raton::actualizar_posicion(double x, double y)
{
	this->posicion_x = x;
	this->posicion_y = y;
}

void Raton::actualizar_desplazamiento(double desplazamiento_y)
{
	this->desplazamiento_y = desplazamiento_y;
}

bool Raton::activado(BotonRaton boton)
{
	if(boton == BotonIzquierdo)
		return this->boton_izquierdo;
	else if(boton == BotonCentral)
		return this->boton_central;
	else if(boton == BotonDerecho)
		return this->boton_derecho;
	return false;
}

double Raton::x()
{
	return this->posicion_x;
}

double Raton::y()
{
	return this->posicion_y;
}

double Raton::dy()
{
	double desplazamiento = this->desplazamiento_y;
	this->desplazamiento_y = 0;
	return desplazamiento;
}
