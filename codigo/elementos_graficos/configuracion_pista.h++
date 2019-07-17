#ifndef CONFIGURACION_PISTA_H
#define CONFIGURACION_PISTA_H

#include "elemento.h++"
#include "../control/pista.h++"
#include <string>

class Configuracion_Pista : public Elemento
{
private:
	//Recursos
	Texto *texto;
	Texto *texto_chico;

	Pista datos_pista;

	//Recursos
	Rectangulo *rectangulo;

public:
	Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos);
	~Configuracion_Pista();

	Pista o_pista();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
