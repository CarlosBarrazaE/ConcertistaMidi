#include "pantalla.h++"

int Pantalla::ancho = 0;
int Pantalla::alto = 0;

int Pantalla::centro_h()
{
	return ancho / 2;
}

int Pantalla::centro_v()
{
	return alto / 2;
}
