#ifndef BARRA_DESPLAZAMIENTO_H
#define BARRA_DESPLAZAMIENTO_H

#include "elemento.h++"
#include <vector>

class Barra_Desplazamiento : public Elemento
{
private:
	int ancho_actual, alto_actual;
	int desplazamiento_x, desplazamiento_y;
	std::vector<Elemento*> elementos;

public:
	Barra_Desplazamiento(int x, int y, int ancho, int alto, Administrador_Recursos *recursos);
	~Barra_Desplazamiento();

	void agregar_elemento(Elemento *e);

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
