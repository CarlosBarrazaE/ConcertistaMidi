#include "ventana.h++"

Ventana::Ventana()
{
	this->accion = Ninguna;
}

Accion Ventana::obtener_accion()
{
	return this->accion;
}
