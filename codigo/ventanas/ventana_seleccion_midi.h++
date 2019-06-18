#ifndef VENTANASELECCIONMIDI_H
#define VENTANASELECCIONMIDI_H

#include "ventana.h++"
#include "../recursos/rectangulo.h++"
#include "../recursos/textura_2d.h++"
#include "../recursos/sombreador.h++"
#include "../elementos/boton.h++"
#include "../pantalla.h++"

class VentanaSeleccionMusica : public Ventana
{
private:
	Rectangulo *fondo;
	Boton *boton_atras;
	Boton *boton_continuar;

	Texto *texto;
	int ajuste_titulo;
public:
	VentanaSeleccionMusica(Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(Raton *raton);
	void dibujar();
};
#endif
