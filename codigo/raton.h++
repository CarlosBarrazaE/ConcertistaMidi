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
	int posicion_x;
	int posicion_y;
	int desplazamiento_x;
	int desplazamiento_y;
	bool boton_izquierdo;
	bool boton_central;
	bool boton_derecho;
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
