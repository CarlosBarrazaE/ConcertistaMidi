#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../recursos/administrador_recursos.h++"
#include "../dispositivos/raton.h++"

class Elemento
{
protected:
	int x, y;
	int ancho, alto;
	bool centrado;
public:
	Elemento(int x, int y, int ancho, int alto);
	Elemento(int x, int y, int ancho, int alto, bool centrado);

	virtual void actualizar(unsigned int diferencia_tiempo) = 0;
	virtual void dibujar() = 0;

	virtual void evento_raton(Raton *raton) = 0;

	int posicion_x();
	int posicion_y();
	int o_ancho();
	int o_alto();

	void posicion_x(int x);
	void posicion_y(int y);
	void e_ancho(int ancho);
	void e_alto(int alto);
};

#endif
