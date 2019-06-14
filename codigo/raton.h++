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
	double posicion_x;
	double posicion_y;
	double desplazamiento_y;
	bool boton_izquierdo;
	bool boton_central;
	bool boton_derecho;
public:
	Raton();
	void actualizar_boton(BotonRaton boton, bool estado);
	void actualizar_posicion(double x, double y);
	void actualizar_desplazamiento(double desplazamiento_y);

	bool activado(BotonRaton boton);
	double x();
	double y();
	double dy();
};

#endif
