#ifndef VENTANASELECCIONMIDI_H
#define VENTANASELECCIONMIDI_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"

class VentanaSeleccionMusica : public Ventana
{
private:
	Rectangulo *rectangulo;
	Textura2D *textura_fondo;

	Boton *boton_atras;
	Boton *boton_continuar;

	Texto *texto;
	int ajuste_titulo;
public:
	VentanaSeleccionMusica(Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(Raton *raton);
	void dibujar();
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
