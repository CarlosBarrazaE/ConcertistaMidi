#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana(), m_texto_velocidad(recursos), m_texto_pausa(recursos)
{
	m_configuracion = configuracion;
	m_musica = musica;

	m_rectangulo = recursos->figura(F_Rectangulo);

	//Carga la configuracion de la base de datos
	std::string resultado_velocidad = m_configuracion->leer("velocidad_musica");

	if(resultado_velocidad != "")
	{
		m_velocidad_musica = std::stod(resultado_velocidad);
		if(m_velocidad_musica <= 0)
			m_velocidad_musica = 0.01;
		else if(m_velocidad_musica > 2)
			m_velocidad_musica = 2;
	}
	else
		m_velocidad_musica = 1.0;

	std::string resultado_teclado = m_configuracion->leer("tipo_teclado");
	if(resultado_teclado != "")
	{
		int teclado_leido = std::stoi(resultado_teclado);
		switch(teclado_leido)
		{
			case 88: m_teclado_actual = Teclas88; break;
			case 76: m_teclado_actual = Teclas76; break;
			case 61: m_teclado_actual = Teclas61; break;
			case 49: m_teclado_actual = Teclas49; break;
			case 37: m_teclado_actual = Teclas37; break;
			default: m_teclado_actual = Teclas88;
		}
	}
	else
		m_teclado_actual = Teclas88;

	Teclado_Configuracion *teclado = Tipo_Teclado::Obtener_teclado(m_teclado_actual);

	m_barra = new Barra_Progreso(0, 40, Pantalla::Ancho, 40, m_musica->musica()->GetSongLengthInMicroseconds(), m_musica->musica()->GetBarLines(), recursos);
	m_organo = new Organo(0, Pantalla::Alto, Pantalla::Ancho, teclado, recursos);
	m_tablero = new Tablero_Notas(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), teclado, recursos);

	m_titulo_musica = new Titulo(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), recursos);
	m_titulo_musica->datos(musica);

	m_texto_velocidad.texto(std::to_string((int)(m_velocidad_musica*100)) + "%");
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

	m_teclas_activas_blancas = m_tablero->blancas_presionadas();
	m_teclas_activas_negras = m_tablero->negras_presionadas();

	//Carga la configuracion de la base de datos de la duracion
	std::string resultado_duracion = m_configuracion->leer("duracion_nota");
	if(resultado_duracion != "")
		m_tablero->modificar_duracion_nota(std::stoi(resultado_duracion));

	//Elimina las notas tocadas antes de esta ventana
	m_configuracion->dispositivo_entrada()->Reset();

	m_cambio_velocidad = false;
	m_pausa = false;

	m_guardar_velocidad = false;
	m_guardar_duracion_nota = false;
	m_guardar_tipo_teclado = false;
}

VentanaOrgano::~VentanaOrgano()
{
	delete m_barra;
	delete m_tablero;
	delete m_organo;
}

void VentanaOrgano::actualizar(unsigned int diferencia_tiempo)
{
	//Cuando termina la cancion se retrocede a la ventana anterior
	if(m_musica->musica()->IsSongOver())
	{
		this->guardar_configuracion();

		m_musica->reiniciar();
		m_accion = CambiarASeleccionPista;
	}

	//Se calculan los microsegundos entre fotogramas para actualizar el midi
	unsigned int microsegundos_actualizar = (diferencia_tiempo / 1000.0) * m_velocidad_musica;

	if(m_pausa)
		microsegundos_actualizar = 0;

	MidiEventListWithTrackId eventos = m_musica->musica()->Update(microsegundos_actualizar);

	if(m_configuracion->dispositivo_salida() != NULL)//Verifica que la salida midi este disponible
	{
		//Se escriben las notas
		std::vector<Pista> *pistas = m_musica->pistas();
		for (MidiEventListWithTrackId::const_iterator i = eventos.begin(); i != eventos.end(); i++)
		{
			//Solo se tocan las pistas que no estan en silencio y que no son tocadas por el jugador
			if(pistas->at(i->first).sonido() && pistas->at(i->first).modo() == Fondo)
			{
				m_configuracion->dispositivo_salida()->Write(i->second);
			}
		}
	}

	//NOTE probando la entrada midi
	MidiEvent evento = m_configuracion->dispositivo_entrada()->Read();
	evento.SetChannel(1);
	evento.SetVelocity(120);

	if(m_configuracion->dispositivo_salida() != NULL)
		m_configuracion->dispositivo_salida()->Write(evento);

	//Almacena las notas tocadas por el jugador
	if(evento.NoteNumber() != 0)
	{
		//Almacena la notas cuando recive el evento NoteOn
		if(evento.Type() == MidiEventType_NoteOn)
		{
			if(!Octava::es_negra(evento.NoteNumber()))
				m_notas_tocadas_blanca.insert(Octava::prosicion_nota(evento.NoteNumber()));
			else
				m_notas_tocadas_negra.insert(Octava::prosicion_nota_negra(evento.NoteNumber()));
		}
		//Elimina las notas cuando recive el evento NoteOff
		else if(evento.Type() == MidiEventType_NoteOff)
		{
			if(!Octava::es_negra(evento.NoteNumber()))
				m_notas_tocadas_blanca.erase(Octava::prosicion_nota(evento.NoteNumber()));
			else
				m_notas_tocadas_negra.erase(Octava::prosicion_nota_negra(evento.NoteNumber()));
		}
	}

	//Establece el color en gris para las notas tocadas por el jugador
	//Sera sobreescrito por el tablero de notas en la etapa de dibujo si la nota tocada es correcta
	for(int id_nota : m_notas_tocadas_blanca)
		m_teclas_activas_blancas->at(id_nota) = Color(0.7f, 0.7f, 0.7f);

	for(int id_nota : m_notas_tocadas_negra)
		m_teclas_activas_negras->at(id_nota) = Color(0.7f, 0.7f, 0.7f);


	//Si selecciono un nuevo tiempo en la barra de progreso, se cambia la posicion.
	if(m_barra->tiempo_seleccionado() > 0)
	{
		m_musica->musica()->GoTo(m_barra->tiempo_seleccionado());
		m_tablero->reiniciar();
		if(m_configuracion->dispositivo_salida() != NULL)
			m_configuracion->dispositivo_salida()->Reset();
	}

	//Cambio de velocidad de la musica
	if(m_cambio_velocidad)
	{
		m_cambio_velocidad = false;
		m_texto_velocidad.texto(std::to_string((int)(m_velocidad_musica*100)) + "%");
	}

	//Se actualizan los componentes
	m_barra->actualizar(diferencia_tiempo);
	m_tablero->actualizar(diferencia_tiempo);
	m_organo->actualizar(diferencia_tiempo);
	m_titulo_musica->actualizar(diferencia_tiempo);

	m_barra->tiempo(m_musica->musica()->GetSongPositionInMicroseconds());
	m_tablero->tiempo(m_musica->musica()->GetSongPositionInMicroseconds());
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

void VentanaOrgano::guardar_configuracion()
{
	//Se guarda la configuracion
	if(m_guardar_velocidad)
		m_configuracion->escribir("velocidad_musica", std::to_string(m_velocidad_musica));
	if(m_guardar_duracion_nota)
		m_configuracion->escribir("duracion_nota", std::to_string(m_tablero->duracion_nota()));//modificar_duracion_nota
	if(m_guardar_tipo_teclado)
		m_configuracion->escribir("tipo_teclado", std::to_string((int)m_teclado_actual));
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
		if(m_configuracion->dispositivo_salida() != NULL)
			m_configuracion->dispositivo_salida()->Reset();

		this->guardar_configuracion();

		m_musica->reiniciar();
		m_accion = CambiarASeleccionPista;
	}
	else if(tecla == TECLA_FLECHA_ARRIBA && estado)
	{
		m_tablero->duracion_nota(1);
		m_guardar_duracion_nota = true;
	}
	else if(tecla == TECLA_FLECHA_ABAJO && estado)
	{
		m_tablero->duracion_nota(-1);
		m_guardar_duracion_nota = true;
	}
	else if(tecla == TECLA_FLECHA_IZQUIERDA && estado)
	{
		m_velocidad_musica-=0.01;
		if(m_velocidad_musica < 0.01)
			m_velocidad_musica = 0.01;
		m_cambio_velocidad = true;
		m_guardar_velocidad = true;
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		m_velocidad_musica+=0.01;
		if(m_velocidad_musica > 2)
			m_velocidad_musica = 2;
		m_cambio_velocidad = true;
		m_guardar_velocidad = true;
	}
	else if(tecla == TECLA_ESPACIO && !estado)
	{
		m_pausa = !m_pausa;
		if(m_pausa)
			if(m_configuracion->dispositivo_salida() != NULL)
				m_configuracion->dispositivo_salida()->Reset();
	}
	else if(tecla == TECLA_F5 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas37));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas37));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_teclado_actual = Teclas37;
		m_guardar_tipo_teclado = true;
	}
	else if(tecla == TECLA_F6 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas49));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas49));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_teclado_actual = Teclas49;
		m_guardar_tipo_teclado = true;
	}
	else if(tecla == TECLA_F7 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas61));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas61));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_teclado_actual = Teclas61;
		m_guardar_tipo_teclado = true;
	}
	else if(tecla == TECLA_F8 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas76));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas76));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_teclado_actual = Teclas76;
		m_guardar_tipo_teclado = true;
	}
	else if(tecla == TECLA_F9 && estado)
	{
		m_tablero->teclado(Tipo_Teclado::Obtener_teclado(Teclas88));
		m_organo->teclado(Tipo_Teclado::Obtener_teclado(Teclas88));
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_teclado_actual = Teclas88;
		m_guardar_tipo_teclado = true;
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	m_barra->dimension(ancho, m_barra->alto());
	m_organo->posicion(m_organo->x(), alto);
	m_organo->dimension(ancho, m_organo->alto());
	m_tablero->dimension(ancho, alto - (m_organo->alto() + m_barra->alto()+40));
	m_titulo_musica->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40));

	m_texto_velocidad.dimension(ancho, 40);
	m_texto_pausa.dimension(ancho, 40);
}
