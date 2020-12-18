#ifndef VENTANASELECCIONPISTA_H
#define VENTANASELECCIONPISTA_H

#include "ventana.h++"
#include "../elementos_graficos/panel_desplazamiento.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/configuracion_pista.h++"
#include "../control/configuracion.h++"
#include "../control/datos_musica.h++"

class VentanaSeleccionPista : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Etiqueta m_texto_titulo;

	//Componentes
	Boton *m_boton_atras;
	Boton *m_boton_continuar;
	Panel_Desplazamiento *m_panel_desplazamiento;
	std::vector<Configuracion_Pista*> m_configuracion_pistas;

	//Datos
	Configuracion *m_configuracion;
	Datos_Musica *m_musica;

	void crear_configuracion(Administrador_Recursos *recursos);
	void cargar_configuracion(Administrador_Recursos *recursos);
 	void guardar_configuracion();
public:
	VentanaSeleccionPista(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaSeleccionPista();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;

	void evento_raton(Raton *raton) override;
	void evento_teclado(Tecla tecla, bool estado) override;
	void evento_pantalla(float ancho, float alto) override;
};
#endif
