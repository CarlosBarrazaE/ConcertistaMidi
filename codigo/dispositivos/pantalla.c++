#include "pantalla.h++"

float Pantalla::Ancho = 0;
float Pantalla::Alto = 0;
bool Pantalla::PantallaCompleta = false;
bool Pantalla::ModoAlambre = false;
bool Pantalla::ModoDesarrollo = false;

float Pantalla::Centro_horizontal()
{
	return Ancho / 2;
}

float Pantalla::Centro_vertical()
{
	return Alto / 2;
}
