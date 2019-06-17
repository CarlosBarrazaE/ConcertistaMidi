#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../recursos/administrador_recursos.h++"
#include "../raton.h++"

class Elemento
{
public:
	Elemento();

	virtual void actualizar(Raton *raton) = 0;
	virtual void dibujar() = 0;
};

#endif
