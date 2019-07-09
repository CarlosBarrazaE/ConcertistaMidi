#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../recursos/administrador_recursos.h++"
#include "../dispositivos/raton.h++"

class Elemento
{
public:
	Elemento();

	virtual void actualizar(unsigned int diferencia_tiempo) = 0;
	virtual void dibujar() = 0;

	virtual void evento_raton(Raton *raton) = 0;
};

#endif
