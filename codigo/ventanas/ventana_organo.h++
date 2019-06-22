#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../recursos/textura_2d.h++"
#include "../elementos/organo.h++"
#include "../pantalla.h++"

class VentanaOrgano : public Ventana
{
private:
	Organo *organo;
public:
	VentanaOrgano(Administrador_Recursos *recursos);
	~VentanaOrgano();

	void actualizar(Raton *raton);
	void dibujar();
};
#endif
