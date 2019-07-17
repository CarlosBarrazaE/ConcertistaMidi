#ifndef BARRA_DESPLAZAMIENTO_H
#define BARRA_DESPLAZAMIENTO_H

#include "elemento.h++"
#include <vector>

class Barra_Desplazamiento : public Elemento
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Textura2D *barra;

	int ancho_actual, alto_actual;
	int desplazamiento_x, desplazamiento_y;
	int columna, fila;
	int margen_columna, margen_fila;
	bool calcular_posicion;
	double proporcion;

	bool sobre_barra;
	bool boton_activado;

	std::vector<Elemento*> elementos;

	void actualizar_dimension();
public:
	Barra_Desplazamiento(int x, int y, int ancho, int alto, int columna, int fila, int margen_columna, int margen_fila, Administrador_Recursos *recursos);
	~Barra_Desplazamiento();

	void agregar_elemento(Elemento *e);

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);

	void c_dimension(int ancho, int alto);
};

#endif
