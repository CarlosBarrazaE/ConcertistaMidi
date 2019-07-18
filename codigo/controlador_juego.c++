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
	this->texto = recursos->obtener_tipografia(LetraChica);

	ventana_actual = new VentanaTitulo(recursos);
/*

	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();
	Registro::aviso("Dispositivos de entrada:");
	for(int x=0; x<dispositivos_entrada.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_entrada[x].name);
	}

	Registro::aviso("Dispositivos de salida:");
	for(int x=0; x<dispositivos_salida.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_salida[x].name);
	}
*/
	this->configuracion.cambiar_entrada(3);
	this->configuracion.cambiar_salida(1);

	this->musica.cargar_midi("../musica/kirby.midi");
	this->musica.e_nombre_musica("Nombre de la canción");
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
	fps = Fps::tiempo_fotograma();
	ventana_actual->actualizar(Fps::obtener_nanosegundos());
	ventana_actual->dibujar();

	if(this->mostrar_fps)
	{
		if(Fps::actualizar_fps())
			texto_fps = "FPS: " + std::to_string((int)fps);
		this->texto->imprimir(10, 20, texto_fps);
	}

	if(ventana_actual->obtener_accion() == CambiarATitulo)
	{
		delete ventana_actual;
		ventana_actual = new VentanaTitulo(this->recursos);
	}
	else if(ventana_actual->obtener_accion() == CambiarASeleccionMusica)
	{
		delete ventana_actual;
		ventana_actual = new VentanaSeleccionMusica(this->recursos);
	}
	else if(ventana_actual->obtener_accion() == CambiarASeleccionPista)
	{
		delete ventana_actual;
		ventana_actual = new VentanaSeleccionPista(&this->musica, this->recursos);
	}
	else if(ventana_actual->obtener_accion() == CambiarAOrgano)
	{
		delete ventana_actual;
		ventana_actual = new VentanaOrgano(&this->configuracion, &this->musica, this->recursos);
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

Raton *Controlador_Juego::o_raton()
{
	return &this->raton;
}

void Controlador_Juego::eventos_raton()
{
	ventana_actual->evento_raton(&this->raton);
}

void Controlador_Juego::eventos_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_F10 && estado)
		this->mostrar_fps = !this->mostrar_fps;
	else if(tecla == TECLA_F11 && estado)
		this->pantalla_completa = !this->pantalla_completa;
	else if(tecla == TECLA_F12 && estado)
		this->modo_alambre = !this->modo_alambre;
	else
		this->ventana_actual->evento_teclado(tecla, estado);
}

void Controlador_Juego::evento_ventana(int ancho, int alto)
{
	Pantalla::ancho = ancho;
	Pantalla::alto = alto;
	recursos->actualizar_pantalla(ancho, alto);
	this->ventana_actual->evento_pantalla(ancho, alto);
}

void Controlador_Juego::evento_salir()
{
	this->finalizar = true;
}
