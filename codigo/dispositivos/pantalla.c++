#include "pantalla.h++"

int Pantalla::Ancho = 0;
int Pantalla::Alto = 0;

int Pantalla::Centro_horizontal()
{
	return Ancho / 2;
}

int Pantalla::Centro_vertical()
{
	return Alto / 2;
}
