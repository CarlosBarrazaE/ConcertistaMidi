#include "controlador_juego.h++"
#include <SDL2/SDL.h>

Controlador_Juego::Controlador_Juego(Administrador_Recursos *recursos)
{
	this->recursos = recursos;
	this->fps = 0;
	this->mostrar_fps = false;
	this->pantalla_completa = false;
	this->modo_alambre = false;
	this->finalizar = false;

	ventana_actual = new VentanaTitulo(recursos);
}

Controlador_Juego::~Controlador_Juego()
{
}

Administrador_Recursos *Controlador_Juego::obtener_administrador_recursos()
{
	return this->recursos;
}

void Controlador_Juego::actualizar()
{
	ventana_actual->actualizar(&this->raton);
	ventana_actual->dibujar();

	if(this->mostrar_fps)
	{
		fps = contador_fps.obtener_fps(SDL_GetTicks() / 1000.0);
		if(contador_fps.nuevo_fps())
			texto_fps = "FPS: " + std::to_string((int)fps);
		this->recursos->mostrar_texto(10, 20, LetraChica, texto_fps);
	}

	if(ventana_actual->obtener_accion() == CambiarATitulo)
	{
		delete ventana_actual;
		ventana_actual = new VentanaTitulo(this->recursos);
	}
	else if(ventana_actual->obtener_accion() == CambiarAConfiguracion)
	{
		delete ventana_actual;
		ventana_actual = new VentanaConfiguracion(this->recursos);
	}
	else if(ventana_actual->obtener_accion() == Salir)
		this->finalizar = true;
}

bool Controlador_Juego::es_pantalla_completa()
{
	return this->pantalla_completa;
}

bool Controlador_Juego::modo_alambre_activado()
{
	return this->modo_alambre;
}

bool Controlador_Juego::terminar()
{
	return this->finalizar;
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
	else if(tecla == TECLA_F12 && estado)
		this->modo_alambre = !this->modo_alambre;
}

void Controlador_Juego::evento_salir()
{
	this->finalizar = true;
}
