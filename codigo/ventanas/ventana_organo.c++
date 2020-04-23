#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana(), m_texto_velocidad(recursos), m_texto_pausa(recursos)
{
	m_configuracion = configuracion;
	m_musica = musica;

	m_rectangulo = recursos->figura(F_Rectangulo);
	Teclado_Configuracion *teclado = Tipo_Teclado::Obtener_teclado(Teclas88);

	m_barra = new Barra_Progreso(0, 40, Pantalla::Ancho, 40, m_musica->musica()->GetSongLengthInMicroseconds(), m_musica->musica()->GetBarLines(), recursos);
	m_organo = new Organo(0, Pantalla::Alto, Pantalla::Ancho, teclado, recursos);
	m_tablero = new Tablero_Notas(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), teclado, recursos);

	m_titulo_musica = new Titulo(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), recursos);
	m_titulo_musica->datos(musica);

	m_velocidad_musica = 1.0;

	m_texto_velocidad.texto("100%");
	m_texto_velocidad.tipografia(recursos->tipografia(LetraTitulo));
	m_texto_velocidad.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_velocidad.posicion(0, 0);
	m_texto_velocidad.dimension(Pantalla::Ancho, 40);
	m_texto_velocidad.centrado(true);

	m_texto_pausa.texto("Pausa");
	m_texto_pausa.tipografia(recursos->tipografia(LetraTitulo));
	m_texto_pausa.color(Color(0.0f, 0.0f, 0.0f));
	m_texto_pausa.posicion(0, 200);
	m_texto_pausa.dimension(Pantalla::Ancho, 40);
	m_texto_pausa.centrado(true);

	m_tablero->notas(m_musica->musica()->Notes());
	m_tablero->pistas(m_musica->pistas());
	m_tablero->lineas(m_musica->musica()->GetBarLines());
	m_organo->blancas_presionadas(m_tablero->blancas_presionadas());
	m_organo->negras_presionadas(m_tablero->negras_presionadas());

	m_cambio_velocidad = false;
	m_pausa = false;
}

VentanaOrgano::~VentanaOrgano()
{
	delete m_barra;
	delete m_tablero;
	delete m_organo;
}

void VentanaOrgano::actualizar(unsigned int diferencia_tiempo)
{
	if(m_musica->musica()->IsSongOver())
	{
		m_musica->reiniciar();
		m_accion = CambiarASeleccionPista;
	}
	unsigned int microsegundos_actualizar = (diferencia_tiempo / 1000.0) * m_velocidad_musica;

	if(m_pausa)
		microsegundos_actualizar = 0;

	MidiEventListWithTrackId evs = m_musica->musica()->Update(microsegundos_actualizar);

	std::vector<Pista> *pistas = m_musica->pistas();
	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); i++)
	{
		if(pistas->at(i->first).sonido())
		{
			if(m_configuracion->salida() != NULL)
				m_configuracion->salida()->Write(i->second);
		}
	}

	if(m_barra->o_tiempo_seleccionado() > 0)
	{
		m_musica->musica()->GoTo(m_barra->o_tiempo_seleccionado());
		m_tablero->reiniciar();
		if(m_configuracion->salida() != NULL)
			m_configuracion->salida()->Reset();
	}

	m_barra->actualizar(diferencia_tiempo);
	m_tablero->actualizar(diferencia_tiempo);
	m_organo->actualizar(diferencia_tiempo);
	m_titulo_musica->actualizar(diferencia_tiempo);

	m_barra->tiempo(m_musica->musica()->GetSongPositionInMicroseconds());
	m_tablero->tiempo(m_musica->musica()->GetSongPositionInMicroseconds());

	if(m_cambio_velocidad)
	{
		m_cambio_velocidad = false;
		m_texto_velocidad.texto(std::to_string((int)(m_velocidad_musica*100)) + "%");
	}
}

void VentanaOrgano::dibujar()
{
	m_tablero->dibujar();
	m_barra->dibujar();
	m_organo->dibujar();
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(0, 0, Pantalla::Ancho, 40, Color(0.141f, 0.624f, 0.933f));
	m_texto_velocidad.dibujar();
	if(m_pausa)
		m_texto_pausa.dibujar();
	m_titulo_musica->dibujar();
}

void VentanaOrgano::evento_raton(Raton *raton)
{
	m_barra->evento_raton(raton);
	m_tablero->evento_raton(raton);
	m_organo->evento_raton(raton);
	m_titulo_musica->evento_raton(raton);
}

void VentanaOrgano::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
	{
		if(m_configuracion->salida() != NULL)
			m_configuracion->salida()->Reset();
		m_musica->reiniciar();
		m_accion = CambiarASeleccionPista;
	}
	else if(tecla == TECLA_FLECHA_ARRIBA && estado)
		m_tablero->velocidad_caida(1);
	else if(tecla == TECLA_FLECHA_ABAJO && estado)
		m_tablero->velocidad_caida(-1);
	else if(tecla == TECLA_FLECHA_IZQUIERDA && estado)
	{
		m_velocidad_musica-=0.01;
		if(m_velocidad_musica < 0.01)
			m_velocidad_musica = 0.01;
		m_cambio_velocidad = true;
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		m_velocidad_musica+=0.01;
		if(m_velocidad_musica > 2)
			m_velocidad_musica = 2;
		m_cambio_velocidad = true;
	}
	else if(tecla == TECLA_ESPACIO && !estado)
	{
		m_pausa = !m_pausa;
		if(m_pausa)
			if(m_configuracion->salida() != NULL)
				m_configuracion->salida()->Reset();
	}
	else if(tecla == TECLA_F5 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas37));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas37));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
	}
	else if(tecla == TECLA_F6 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas49));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas49));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
	}
	else if(tecla == TECLA_F7 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas61));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas61));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
	}
	else if(tecla == TECLA_F8 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas76));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas76));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
	}
	else if(tecla == TECLA_F9 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas88));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas88));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	m_barra->ancho(ancho);
	m_organo->y(alto);
	m_organo->ancho(ancho);
	m_tablero->dimension(ancho, alto - (m_organo->alto() + m_barra->alto()+40));

	m_texto_velocidad.dimension(ancho, 40);
	m_texto_pausa.dimension(ancho, 40);

	m_barra->evento_pantalla(ancho, alto);
	m_organo->evento_pantalla(ancho, alto);
	m_tablero->evento_pantalla(ancho, alto);
	m_titulo_musica->evento_pantalla(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40));
}
