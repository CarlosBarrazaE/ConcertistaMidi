#ifndef VENTANASELECCIONMUSICA_H
#define VENTANASELECCIONMUSICA_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"

class VentanaSeleccionMusica : public Ventana
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Textura2D *textura_fondo;
	Texto *texto;

	//Componentes
	Boton *boton_atras;
	Boton *boton_continuar;

	//Texto pantalla
	int ajuste_titulo;
public:
	VentanaSeleccionMusica(Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
