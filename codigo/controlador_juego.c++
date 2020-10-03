#include "controlador_juego.h++"
#include <SDL2/SDL.h>

Controlador_Juego::Controlador_Juego(Administrador_Recursos *recursos) : m_texto_fps(recursos), m_informacion(recursos), m_notificaciones(recursos)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_notificaciones.posicion(Pantalla::Centro_horizontal(), 165);

	m_texto_fps.tipografia(recursos->tipografia(LetraChica));
	m_texto_fps.posicion(10, 0);
	m_texto_fps.dimension(40, 40);
	m_texto_fps.centrado_vertical(true);

	m_informacion.tipografia(recursos->tipografia(LetraChica));

	m_ventana_actual = new VentanaTitulo(recursos);

	//Control dinamico de fps
	m_fps_dinamico = true;
	m_fps_reducido = false;
	m_contador_inactividad = 0;

	//Grabar pantalla
	m_fotograma = -1;

	m_depurar = false;
	m_modo_alambre = false;
	m_finalizar = false;
	m_guardar_cambios = false;

	std::string resultado_pantalla_completa = m_configuracion.leer("pantalla_completa");
	if(resultado_pantalla_completa == "verdadero")
		m_pantalla_completa = true;
	else
		m_pantalla_completa = false;
}

Controlador_Juego::~Controlador_Juego()
{
	delete m_ventana_actual;
}

Administrador_Recursos *Controlador_Juego::obtener_administrador_recursos()
{
	return m_recursos;
}

void Controlador_Juego::actualizar()
{
	unsigned int fps = Fps::Calcular_tiempo();
	unsigned int diferencia_tiempo = Fps::Obtener_nanosegundos();
	//unsigned int diferencia_tiempo = (1.0/60.0)*1000000000;

	//Reconecta los dispositivos midis si es necesario
	m_configuracion.reconectar();

	m_ventana_actual->actualizar(diferencia_tiempo);
	m_notificaciones.actualizar(diferencia_tiempo);
	m_ventana_actual->dibujar();
	m_notificaciones.dibujar();

	if(m_depurar)
	{
		if(Fps::Actualizar_fps())
			m_texto_fps.texto("FPS: " + std::to_string(fps));
		m_texto_fps.dibujar();

		//Dibuja Raton
		m_rectangulo->textura(false);
		m_rectangulo->dibujar(static_cast<float>(m_raton.x())-11, static_cast<float>(m_raton.y()), 21, 1, Color(1.0f, 0.0f, 0.0f));
		m_rectangulo->dibujar(static_cast<float>(m_raton.x()), static_cast<float>(m_raton.y())-11, 1, 21, Color(1.0f, 0.0f, 0.0f));

		m_informacion.posicion(static_cast<float>(m_raton.x()+2), static_cast<float>(m_raton.y()-15));
		m_informacion.texto("X: " + std::to_string(m_raton.x()) + " Y: " + std::to_string(m_raton.y()));
		m_informacion.dibujar();
	}

	bool cambio_ventana = false;

	if(m_ventana_actual->obtener_accion() == CambiarATitulo)
	{
		delete m_ventana_actual;
		m_fps_dinamico = true;
		m_ventana_actual = new VentanaTitulo(m_recursos);
		cambio_ventana = true;
	}
	else if(m_ventana_actual->obtener_accion() == CambiarASeleccionMusica)
	{
		delete m_ventana_actual;
		m_fps_dinamico = true;
		m_ventana_actual = new VentanaSeleccionMusica(&m_configuracion, &m_musica, m_recursos);
		cambio_ventana = true;
	}
	else if(m_ventana_actual->obtener_accion() == CambiarASeleccionPista)
	{
		delete m_ventana_actual;
		m_fps_dinamico = true;
		m_ventana_actual = new VentanaSeleccionPista(&m_configuracion, &m_musica, m_recursos);
		cambio_ventana = true;

		m_fotograma = -1;
	}
	else if(m_ventana_actual->obtener_accion() == CambiarAOrgano)
	{
		delete m_ventana_actual;
		m_fps_dinamico = false;
		m_ventana_actual = new VentanaOrgano(&m_configuracion, &m_musica, m_recursos);
		cambio_ventana = true;

		m_fotograma++;
	}
	else if(m_ventana_actual->obtener_accion() == CambiarAConfiguracion)
	{
		delete m_ventana_actual;
		m_fps_dinamico = true;
		m_ventana_actual = new VentanaConfiguracion(&m_configuracion, m_recursos);
		cambio_ventana = true;
	}
	else if(m_ventana_actual->obtener_accion() == Salir)
		this->evento_salir();

	if(cambio_ventana)
	{
		//Reenvia el ultimo evento del raton
		m_ventana_actual->evento_raton(&m_raton);
	}

	if(m_fotograma >= 0)
	{
		m_fotograma++;
		if(m_fotograma > 1)
		{
			//Se omite el primer fotograma porque aun muestra la ventana anterior
			/*float *pixeles = new float[Pantalla::Ancho*Pantalla::Alto*4];
			glReadPixels(0, 0, Pantalla::Ancho, Pantalla::Alto, GL_RGBA, GL_FLOAT, pixeles);
			Archivo::Tga::Escribir("../fotogramas/" + std::to_string(m_fotograma-1) + ".tga", pixeles, Pantalla::Ancho, Pantalla::Alto);
			delete[] pixeles;*/
		}
	}

	if(m_notificaciones.mostrando_notificaciones())
		this->reiniciar_contador_inactividad();

	if(!m_fps_reducido)
		m_contador_inactividad += (static_cast<float>(diferencia_tiempo)/1000000000.0f);

	if(m_contador_inactividad > 5 && !m_fps_reducido && m_fps_dinamico)
	{
		//Reduce a 1/4 los fps si se mantiene inactivo durante 5 segundos
		m_fps_reducido = true;
		SDL_GL_SetSwapInterval(4);
	}
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

Raton *Controlador_Juego::raton()
{
	return &m_raton;
}

void Controlador_Juego::eventos_raton()
{
	m_ventana_actual->evento_raton(&m_raton);
	this->reiniciar_contador_inactividad();
}

void Controlador_Juego::eventos_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_F10 && estado)
		m_depurar = !m_depurar;
	else if(tecla == TECLA_F11 && estado)
	{
		m_pantalla_completa = !m_pantalla_completa;
		m_guardar_cambios = !m_guardar_cambios;
	}
	else if(tecla == TECLA_F12 && estado)
		m_modo_alambre = !m_modo_alambre;
	else
	{
		m_ventana_actual->evento_teclado(tecla, estado);
		unsigned char nota = Teclado::Tecla_a_nota(tecla);
		if(nota < 255)
		{
			if(estado)
			{
				if(m_teclas_pulsadas.count(nota) == 0)
				{
					m_teclas_pulsadas.insert(nota);
					sendNote(nota, true);
				}
			}
			else
			{
				if(m_teclas_pulsadas.count(nota) > 0)
				{
					m_teclas_pulsadas.erase(nota);
					sendNote(nota, false);
				}
			}
		}
	}
	this->reiniciar_contador_inactividad();
}

void Controlador_Juego::evento_ventana(float ancho, float alto)
{
	Pantalla::Ancho = ancho;
	Pantalla::Alto = alto;
	m_recursos->actualizar_pantalla(ancho, alto);
	m_ventana_actual->evento_pantalla(ancho, alto);
	m_notificaciones.posicion(Pantalla::Centro_horizontal(), 165);
	this->reiniciar_contador_inactividad();
}

void Controlador_Juego::evento_salir()
{
	m_finalizar = true;
	//Se guarda solo si hay cambios
	if(m_guardar_cambios)
	{
		if(m_pantalla_completa)
			m_configuracion.escribir("pantalla_completa", "verdadero");
		else
			m_configuracion.escribir("pantalla_completa", "falso");
	}
}

void Controlador_Juego::reiniciar_contador_inactividad()
{
	//Vuelve a los fps maximo
	m_contador_inactividad = 0;
	if(m_fps_reducido)
	{
		m_fps_reducido = false;
		SDL_GL_SetSwapInterval(1);
	}
}
