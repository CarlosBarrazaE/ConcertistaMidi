#ifndef CONTROLADOR_JUEGO_H
#define CONTROLADOR_JUEGO_H

#include "recursos/administrador_recursos.h++"
#include "archivos/imagen_tga.h++"
#include "elementos_graficos/etiqueta.h++"
#include "dispositivos/teclas.h++"
#include "dispositivos/raton.h++"
#include "dispositivos/pantalla.h++"
#include "fps.h++"

#include "ventanas/ventana.h++"
#include "ventanas/ventana_titulo.h++"
#include "ventanas/ventana_seleccion_musica.h++"
#include "ventanas/ventana_seleccion_pista.h++"
#include "ventanas/ventana_organo.h++"
#include "ventanas/ventana_configuracion.h++"

#include "control/configuracion.h++"
#include "control/datos_musica.h++"

class Controlador_Juego
{
private:
	Administrador_Recursos *m_recursos;
	Etiqueta m_texto_fps;
	double m_fps;

	//Control
	bool m_mostrar_fps;
	bool m_pantalla_completa;
	bool m_modo_alambre;
	bool m_finalizar;

	//Eventos
	Raton m_raton;
	Ventana *m_ventana_actual;

	Configuracion m_configuracion;
	Datos_Musica m_musica;

	int m_fotograma;

	//Configuracion bd
	//Usuario
public:
	Controlador_Juego(Administrador_Recursos *recursos);
	~Controlador_Juego();
	Administrador_Recursos *obtener_administrador_recursos();
	void actualizar();

	bool es_pantalla_completa();
	bool modo_alambre_activado();
	bool terminar();

	Raton *o_raton();

	void eventos_raton();
	void eventos_teclado(Tecla tecla, bool estado);
	void evento_ventana(int ancho, int alto);
	void evento_salir();
};

#endif
