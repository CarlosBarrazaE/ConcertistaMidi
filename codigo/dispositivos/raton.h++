#ifndef RATON_H
#define RATON_H

enum BotonRaton
{
	BotonIzquierdo,
	BotonCentral,
	BotonDerecho
};

class Raton
{
private:
	int m_posicion_x, m_posicion_y;
	int m_desplazamiento_x, m_desplazamiento_y;
	bool m_boton_izquierdo, m_boton_central, m_boton_derecho;
public:
	Raton();
	void actualizar_boton(BotonRaton boton, bool estado);
	void actualizar_posicion(int x, int y);
	void actualizar_desplazamiento(int desplazamiento_x, int desplazamiento_y);

	bool activado(BotonRaton boton);
	int x();
	int y();
	int dx();
	int dy();
};

#endif
