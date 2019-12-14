#include "controlador_juego.h++"
#include <SDL2/SDL.h>

Controlador_Juego::Controlador_Juego(Administrador_Recursos *recursos)
{
	m_recursos = recursos;
	m_fps = 0;
	m_mostrar_fps = false;
	m_pantalla_completa = false;
	m_modo_alambre = false;
	m_finalizar = false;

	m_texto_fps.tipografia(recursos->obtener_tipografia(LetraChica));
	m_texto_fps.posicion(10, 20);

	m_ventana_actual = new VentanaTitulo(recursos);

	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();
/*
	Registro::Aviso("Dispositivos de entrada:");
	for(int x=0; x<dispositivos_entrada.size(); x++)
	{
		Registro::Aviso("\tNombre: " + dispositivos_entrada[x].name);
	}

	Registro::Aviso("Dispositivos de salida:");
	for(int x=0; x<dispositivos_salida.size(); x++)
	{
		Registro::Aviso("\tNombre: " + dispositivos_salida[x].name);
	}
*/
	if(dispositivos_salida.size() < 2)
		Registro::Error("Sintetizador midi no encontrado");
	m_configuracion.cambiar_entrada(3);
	m_configuracion.cambiar_salida(1);

	m_musica.cargar_midi("../musica/Una espiga.mid");
	m_musica.e_nombre_musica("Nombre de la canción");
}

Controlador_Juego::~Controlador_Juego()
{
}

Administrador_Recursos *Controlador_Juego::obtener_administrador_recursos()
{
	return m_recursos;
}

void Controlador_Juego::actualizar()
{
	m_fps = Fps::Tiempo_fotograma();
	m_ventana_actual->actualizar(Fps::Obtener_nanosegundos());
	m_ventana_actual->dibujar();

	if(m_mostrar_fps)
	{
		if(Fps::Actualizar_fps())
			m_texto_fps.texto("FPS: " + std::to_string((int)m_fps));
		m_texto_fps.dibujar();
	}

	if(m_ventana_actual->obtener_accion() == CambiarATitulo)
	{
		delete m_ventana_actual;
		m_ventana_actual = new VentanaTitulo(m_recursos);
	}
	else if(m_ventana_actual->obtener_accion() == CambiarASeleccionMusica)
	{
		delete m_ventana_actual;
		m_ventana_actual = new VentanaSeleccionMusica(m_recursos);
	}
	else if(m_ventana_actual->obtener_accion() == CambiarASeleccionPista)
	{
		delete m_ventana_actual;
		m_ventana_actual = new VentanaSeleccionPista(&m_musica, m_recursos);
	}
	else if(m_ventana_actual->obtener_accion() == CambiarAOrgano)
	{
		delete m_ventana_actual;
		m_ventana_actual = new VentanaOrgano(&m_configuracion, &m_musica, m_recursos);
	}
	else if(m_ventana_actual->obtener_accion() == CambiarAConfiguracion)
	{
		delete m_ventana_actual;
		m_ventana_actual = new VentanaConfiguracion(m_recursos);
	}
	else if(m_ventana_actual->obtener_accion() == Salir)
		m_finalizar = true;
}

bool Controlador_Juego::es_pantalla_completa()
{
	return m_pantalla_completa;
}

bool Controlador_Juego::modo_alambre_activado()
{
	return m_modo_alambre;
}

bool Controlador_Juego::terminar()
{
	return m_finalizar;
}

Raton *Controlador_Juego::o_raton()
{
	return &m_raton;
}

void Controlador_Juego::eventos_raton()
{
	m_ventana_actual->evento_raton(&m_raton);
}

void Controlador_Juego::eventos_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_F10 && estado)
		m_mostrar_fps = !m_mostrar_fps;
	else if(tecla == TECLA_F11 && estado)
		m_pantalla_completa = !m_pantalla_completa;
	else if(tecla == TECLA_F12 && estado)
		m_modo_alambre = !m_modo_alambre;
	else
		m_ventana_actual->evento_teclado(tecla, estado);
}

void Controlador_Juego::evento_ventana(int ancho, int alto)
{
	Pantalla::Ancho = ancho;
	Pantalla::Alto = alto;
	m_recursos->actualizar_pantalla(ancho, alto);
	m_ventana_actual->evento_pantalla(ancho, alto);
}

void Controlador_Juego::evento_salir()
{
	m_finalizar = true;
}
