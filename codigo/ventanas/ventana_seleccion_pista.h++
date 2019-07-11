#ifndef VENTANASELECCIONPISTA_H
#define VENTANASELECCIONPISTA_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"

class VentanaSeleccionPista : public Ventana
{
private:
	Rectangulo *rectangulo;
	Texto *texto;

	Boton *boton_atras;
	Boton *boton_continuar;

	int ajuste_titulo;
public:
	VentanaSeleccionPista(Administrador_Recursos *recursos);
	~VentanaSeleccionPista();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
