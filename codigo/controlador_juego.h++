#ifndef CONTROLADOR_JUEGO_H
#define CONTROLADOR_JUEGO_H

#include "recursos/administrador_recursos.h++"
#include "archivos/imagen_tga.h++"
#include "elementos_graficos/etiqueta.h++"
#include "elementos_graficos/notificacion.h++"
#include "dispositivos/teclas.h++"
#include "dispositivos/teclado.h++"
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

#include "libmidi/MidiComm.h++"

class Controlador_Juego
{
private:
	Administrador_Recursos *m_recursos;
	Etiqueta m_texto_fps;
	Notificacion m_notificaciones;
	double m_fps;
	bool m_fps_reducido;
	bool m_fps_reducido_desactivado;
	int m_contador_inactividad;
	Rectangulo *m_rectangulo;

	//Control
	bool m_depurar;
	bool m_pantalla_completa;
	bool m_modo_alambre;
	bool m_finalizar;
	bool m_guardar_cambios;
	std::set<int> m_teclas_pulsadas;

	//Eventos
	Raton m_raton;
	Ventana *m_ventana_actual;

	Configuracion m_configuracion;
	Datos_Musica m_musica;

	int m_fotograma;

	//Configuracion bd
	//Usuario

	void control_fps(bool activo);
public:
	Controlador_Juego(Administrador_Recursos *recursos);
	~Controlador_Juego();
	Administrador_Recursos *obtener_administrador_recursos();
	void actualizar();

	bool es_pantalla_completa();
	bool modo_alambre_activado();
	bool terminar();

	Raton *raton();

	void eventos_raton();
	void eventos_teclado(Tecla tecla, bool estado);
	void evento_ventana(int ancho, int alto);
	void evento_salir();
};

#endif
