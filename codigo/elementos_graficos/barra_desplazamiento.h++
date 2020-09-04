#ifndef BARRA_DESPLAZAMIENTO_H
#define BARRA_DESPLAZAMIENTO_H

#include "elemento.h++"
#include "../dispositivos/pantalla.h++"
#include <vector>

class Barra_Desplazamiento : public Elemento
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Textura2D *m_barra;

	int m_ancho_actual, m_alto_actual;
	int m_desplazamiento_x, m_desplazamiento_y;
	int m_columna, m_fila;
	int m_margen_columna, m_margen_fila;
	bool m_calcular_posicion;
	double m_proporcion;

	bool m_sobre_barra;
	bool m_boton_activado;

	std::vector<Elemento*> m_elementos;

	void actualizar_dimension();
public:
	Barra_Desplazamiento(int x, int y, int ancho, int alto, int columna, int fila, int margen_columna, int margen_fila, Administrador_Recursos *recursos);
	~Barra_Desplazamiento();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(int ancho, int alto) override;

	void agregar_elemento(Elemento *e);
	void vaciar();
};

#endif
