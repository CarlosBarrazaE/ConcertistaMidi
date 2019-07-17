#include "configuracion_pista.h++"
#include "../registro.h++"

Configuracion_Pista::Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto), datos_pista(pista)
{
	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
	this->texto = recursos->obtener_tipografia(LetraMediana);
	this->texto_chico = recursos->obtener_tipografia(LetraMuyChica);
}

Configuracion_Pista::~Configuracion_Pista()
{

}

Pista Configuracion_Pista::o_pista()
{
	return this->datos_pista;
}

void Configuracion_Pista::actualizar(unsigned int diferencia_tiempo)
{

}

void Configuracion_Pista::dibujar()
{
	this->rectangulo->textura(false);
	this->rectangulo->dibujar(this->x, this->y, this->ancho, this->alto, this->datos_pista.o_color());
	this->texto->imprimir(this->x+20, this->y+40, this->datos_pista.o_instrumento(), Color(1.0f, 1.0f, 1.0f));
	this->texto_chico->imprimir(this->x+20, this->y+55, std::to_string(this->datos_pista.o_numero_notas()) + " notas", Color(1.0f, 1.0f, 1.0f));
}

void Configuracion_Pista::evento_raton(Raton *raton)
{

}
