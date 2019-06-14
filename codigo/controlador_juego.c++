#include "controlador_juego.h++"
#include <GLFW/glfw3.h>

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
		fps = contador_fps.obtener_fps(glfwGetTime());
		if(contador_fps.nuevo_fps())
			texto_fps = "FPS: " + std::to_string((int)fps);

		this->recursos->mostrar_texto(10, 20, LetraChica, texto_fps);
	}
}

Raton *Controlador_Juego::eventos_raton()
{
	return &this->raton;
}

void Controlador_Juego::eventos_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_F10 && estado)
		this->mostrar_fps = !this->mostrar_fps;
	if(tecla == TECLA_F11 && estado)
		this->pantalla_completa = !this->pantalla_completa;
}
