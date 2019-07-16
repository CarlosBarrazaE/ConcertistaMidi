#ifndef VENTANASELECCIONPISTA_H
#define VENTANASELECCIONPISTA_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/configuracion_pista.h++"
#include "../control/configuracion.h++"
#include "../control/datos_musica.h++"

class VentanaSeleccionPista : public Ventana
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Texto *texto;

	//Componentes
	Boton *boton_atras;
	Boton *boton_continuar;
	std::vector<Configuracion_Pista> configuracion_pistas;

	//Texto pantalla
	int ajuste_titulo;

	//Datos
	Datos_Musica *musica;
public:
	VentanaSeleccionPista(Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaSeleccionPista();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
