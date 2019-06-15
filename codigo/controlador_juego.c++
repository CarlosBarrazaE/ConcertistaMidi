#include "controlador_juego.h++"
#include <SDL2/SDL.h>

Controlador_Juego::Controlador_Juego(Administrador_Recursos *recursos)
{
	this->recursos = recursos;
	this->fps = 0;
	this->mostrar_fps = false;
	this->pantalla_completa = false;
	this->finalizar = false;
}

Controlador_Juego::~Controlador_Juego()
{
}

Administrador_Recursos *Controlador_Juego::obtener_administrador_recursos()
{
	return this->recursos;
}

bool Controlador_Juego::es_pantalla_completa()
{
	return this->pantalla_completa;
}

bool Controlador_Juego::terminar()
{
	return finalizar;
}

void Controlador_Juego::actualizar()
{
	if(this->mostrar_fps)
	{
		fps = contador_fps.obtener_fps(SDL_GetTicks() / 1000.0);
		if(contador_fps.nuevo_fps())
			texto_fps = "FPS: " + std::to_string((int)fps);

		this->recursos->mostrar_texto(10, 20, LetraChica, texto_fps);

	}

	this->recursos->mostrar_texto(raton.x()+20, raton.y()+15, LetraMediana, "<-- Esa es la flechita, dx:" + std::to_string(raton.dx()) + " dy:"  + std::to_string(raton.dy()), Color(240, 20, 100));
	int alto = 35;
	if(raton.activado(BotonIzquierdo))
	{
		this->recursos->mostrar_texto(raton.x()+40, raton.y()+alto, LetraMediana, "Clic Izquierdo", Color(50, 180, 100));
		alto += 20;
	}
	if(raton.activado(BotonCentral))
	{
		this->recursos->mostrar_texto(raton.x()+40, raton.y()+alto, LetraMediana, "Clic Central", Color(100, 20, 240));
		alto += 20;
	}
	if(raton.activado(BotonDerecho))
		this->recursos->mostrar_texto(raton.x()+40, raton.y()+alto, LetraMediana, "Clic Derecho", Color(20, 100, 240));
}

Raton *Controlador_Juego::eventos_raton()
{
	return &this->raton;
}

void Controlador_Juego::eventos_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_F10 && estado)
		this->mostrar_fps = !this->mostrar_fps;
	else if(tecla == TECLA_F11 && estado)
		this->pantalla_completa = !this->pantalla_completa;
	else if(tecla == TECLA_ESCAPE)
		this->finalizar = true;
}

void Controlador_Juego::evento_salir()
{
	this->finalizar = true;
}
