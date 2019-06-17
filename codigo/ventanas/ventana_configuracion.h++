#ifndef VENTANACONFIGURACION_H
#define VENTANACONFIGURACION_H

#include "ventana.h++"
#include "../elementos/boton.h++"
#include "../recursos/textura_2d.h++"

class VentanaConfiguracion : public Ventana
{
private:
	Boton *boton_atras;
public:
	VentanaConfiguracion(Administrador_Recursos *recursos);
	~VentanaConfiguracion();

	void actualizar(Raton *raton);
	void dibujar();
};
#endif