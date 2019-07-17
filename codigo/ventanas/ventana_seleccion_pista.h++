#ifndef VENTANASELECCIONPISTA_H
#define VENTANASELECCIONPISTA_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/configuracion_pista.h++"
#include "../elementos_graficos/barra_desplazamiento.h++"
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
	Barra_Desplazamiento *barra_desplazamiento;
	std::vector<Configuracion_Pista*> configuracion_pistas;

	//Texto pantalla
	int ajuste_titulo;

	//Datos
	Datos_Musica *musica;

	void crear_configuracion(Administrador_Recursos *recursos);
	void cargar_configuracion(Administrador_Recursos *recursos);
 	void guardar_configuracion();
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
