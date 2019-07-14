#ifndef CONFIGURACION_PISTA_H
#define CONFIGURACION_PISTA_H

#include "elemento.h++"

class Configuracion_Pista : Elemento
{
private:
	int x, y, ancho, alto;

	//Recursos
	Rectangulo *rectangulo;

public:
	Configuracion_Pista(int x, int y, Administrador_Recursos *recursos);
	~Configuracion_Pista();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
