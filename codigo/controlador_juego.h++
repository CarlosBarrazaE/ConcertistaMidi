#ifndef CONTROLADOR_JUEGO_H
#define CONTROLADOR_JUEGO_H

#include "recursos/administrador_recursos.h++"
#include "teclas.h++"
#include "raton.h++"
#include "fps.h++"

#include "ventanas/ventana.h++"
#include "ventanas/ventana_titulo.h++"
#include "ventanas/ventana_seleccion_midi.h++"
#include "ventanas/ventana_organo.h++"
#include "ventanas/ventana_configuracion.h++"

class Controlador_Juego
{
private:
	Administrador_Recursos *recursos;
	double fps;
	std::string texto_fps;

	//Control
	bool mostrar_fps;
	bool pantalla_completa;
	bool modo_alambre;
	bool finalizar;

	//Eventos
	Raton raton;
	Ventana *ventana_actual;
	//Configuracion bd
	//Usuario
	//Midis
public:
	Controlador_Juego(Administrador_Recursos *recursos);
	~Controlador_Juego();
	Administrador_Recursos *obtener_administrador_recursos();
	void actualizar();

	bool es_pantalla_completa();
	bool modo_alambre_activado();
	bool terminar();

	Raton *eventos_raton();
	void eventos_teclado(Tecla tecla, bool estado);
	void evento_salir();
};

#endif
