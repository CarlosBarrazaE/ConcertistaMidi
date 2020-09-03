#ifndef FILA_H
#define FILA_H

#include "elemento.h++"
#include "etiqueta.h++"

#include <vector>

class Fila : public Elemento
{
private:
	std::vector<Etiqueta *> m_celda;
	bool m_sobre_boton, m_boton_pre_activado, m_boton_seleccionado;

	Rectangulo *m_rectangulo;
	Color m_color_fondo, m_color_seleccion, m_color_sobre, m_color_actual;
public:
	Fila(int x, int y, int ancho, int alto, Administrador_Recursos *recursos);
	~Fila();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;
	void evento_pantalla(int ancho, int alto) override;

	void agregar_celda(Etiqueta *celda);

	bool esta_seleccionado();
	void seleccionar();
	void deseleccionar();
};

#endif
