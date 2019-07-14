#include "configuracion_pista.h++"

Configuracion_Pista::Configuracion_Pista(int x, int y, Administrador_Recursos *recursos)
{
	this->x = x;
	this->y = y;
	this->ancho = 200;
	this->alto = 200;

	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
}

Configuracion_Pista::~Configuracion_Pista()
{

}

void Configuracion_Pista::actualizar(unsigned int diferencia_tiempo)
{

}

void Configuracion_Pista::dibujar()
{
	this->rectangulo->textura(false);
	this->rectangulo->dibujar(this->x, this->y, this->ancho, this->alto, Color(0.54f, 1.0f, 0.5f));
}

void Configuracion_Pista::evento_raton(Raton *raton)
{

}
