#ifndef CONTROLADOR_JUEGO_H
#define CONTROLADOR_JUEGO_H

#include "recursos/administrador_recursos.h++"
#include "teclas.h++"
#include "raton.h++"
#include "fps.h++"

class Controlador_Juego
{
private:
	Administrador_Recursos *recursos;
	Fps contador_fps;
	double fps;
	std::string texto_fps;

	//Control
	bool mostrar_fps;
	bool pantalla_completa;
	bool finalizar;

	//Eventos
	Raton raton;
	//Ventana Actual
	//Configuracion bd
	//Usuario
	//Midis
public:
	Controlador_Juego(Administrador_Recursos *recursos);
	~Controlador_Juego();
	Administrador_Recursos *obtener_administrador_recursos();
	bool es_pantalla_completa();
	bool terminar();
	void actualizar();

	Raton *eventos_raton();
	void eventos_teclado(Tecla tecla, bool estado);
	void evento_salir();
};

#endif
