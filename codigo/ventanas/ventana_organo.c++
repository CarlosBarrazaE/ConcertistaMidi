#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana(), m_texto_velocidad(recursos), m_texto_pausa(recursos), m_subtitulos(recursos)
{
	m_configuracion = configuracion;
	m_musica = musica;

	m_rectangulo = recursos->figura(F_Rectangulo);
	m_textura_subtitulo = recursos->textura(T_Nota);

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
		m_teclado_actual.cargar(resultado_teclado);

	m_barra = new Barra_Progreso(0, 40, Pantalla::Ancho, 40, m_musica->musica()->GetSongLengthInMicroseconds(), m_musica->musica()->GetBarLines(), recursos);
	m_organo = new Organo(0, Pantalla::Alto, Pantalla::Ancho, &m_teclado_actual, recursos);
	m_tablero = new Tablero_Notas(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), &m_teclado_actual, recursos);

	m_titulo_musica = new Titulo(0, m_barra->alto()+40, Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40), recursos);
	m_titulo_musica->datos(musica);

	m_texto_velocidad.texto(std::to_string(static_cast<int>(m_velocidad_musica*100)) + "%");
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

	m_subtitulos.texto("");
	m_subtitulos.tipografia(recursos->tipografia(LetraTitulo));
	m_subtitulos.color(Color(0.0f, 0.0f, 0.0f));
	m_subtitulos.posicion(0, 100);
	m_subtitulos.dimension(Pantalla::Ancho, 20);
	m_subtitulos.centrado(true);

	m_tablero->notas(m_musica->musica()->Notes());
	m_tablero->pistas(m_musica->pistas());
	m_tablero->lineas(m_musica->musica()->GetBarLines());
	m_organo->estado_teclas(m_tablero->estado_teclas());

	m_teclas_activas = m_tablero->estado_teclas();

	//Carga la configuracion de la base de datos de la duracion
	std::string resultado_duracion = m_configuracion->leer("duracion_nota");
	if(resultado_duracion != "")
		m_tablero->modificar_duracion_nota(std::stoi(resultado_duracion));

	//Elimina las notas tocadas antes de esta ventana
	m_configuracion->dispositivo_entrada()->Reset();

	m_cambio_velocidad = false;
	m_pausa = false;
	m_retorno_carro = false;

	//Carga la configuracion de los subtitulos
	std::string estado_subtitulo = m_configuracion->leer("estado_subtitulo");
	if(estado_subtitulo == "inactivo")
		m_mostrar_subtitulo = false;
	else
		m_mostrar_subtitulo = true;

	m_guardar_velocidad = false;
	m_guardar_duracion_nota = false;
	m_guardar_tipo_teclado = false;
	m_guardar_estado_subtitulo = false;
}

VentanaOrgano::~VentanaOrgano()
{
	m_configuracion->dispositivo_entrada()->Reset();
	if(m_configuracion->dispositivo_salida() != NULL)
		m_configuracion->dispositivo_salida()->Reset();
	delete m_titulo_musica;
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
	unsigned int microsegundos_actualizar = static_cast<unsigned int>((static_cast<double>(diferencia_tiempo) / 1000.0) * m_velocidad_musica);

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
			//Letra de archivo midi
			if(i->second.HasText() && i->second.MetaType() == MidiMetaEvent_Lyric)
			{
				std::string nuevo_texto = i->second.Text();
				std::replace(nuevo_texto.begin(), nuevo_texto.end(), '_', ' ');

				//Retorno de carro para la proxima linea
				if(nuevo_texto.length() > 0 && (nuevo_texto[0] == '\r' || nuevo_texto[0] == '\n'))
					m_retorno_carro = true;
				else
				{
					if(m_subtitulo_texto.length() >= 80 || m_retorno_carro)
					{
						m_subtitulo_texto = nuevo_texto;
						m_retorno_carro = false;
					}
					else
						m_subtitulo_texto += nuevo_texto;
				}

				if(Texto::esta_vacio(m_subtitulo_texto) && m_subtitulo_texto.length() > 0)
					m_subtitulo_texto = "";

				if(m_mostrar_subtitulo)
					m_subtitulos.texto(m_subtitulo_texto);
			}
			//Midi karaoke
			else if(i->second.HasText() && i->second.MetaType() == MidiMetaEvent_Text && i->second.GetDeltaPulses() > 0)
			{
				std::string nuevo_texto = i->second.Text();
				std::replace(nuevo_texto.begin(), nuevo_texto.end(), '_', ' ');

				//Retorno de carro para la proxima linea
				if(nuevo_texto.length() > 0 && (nuevo_texto[0] == '\\' || nuevo_texto[0] == '/'))
				{
					std::string recortado = nuevo_texto.substr(1);//Quita el primer caracter
					m_subtitulo_texto = recortado;
				}
				else
					m_subtitulo_texto += nuevo_texto;

				if(Texto::esta_vacio(m_subtitulo_texto) && m_subtitulo_texto.length() > 0)
					m_subtitulo_texto = "";

				if(m_mostrar_subtitulo)
					m_subtitulos.texto(m_subtitulo_texto);
			}
			/*
			if(i->second.MetaType() == MidiMetaEvent_Copyright)
				Registro::Depurar("Evento Meta: MidiMetaEvent_Copyright Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_TrackName)
				Registro::Depurar("Evento Meta: MidiMetaEvent_TrackName Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_Instrument)
				Registro::Depurar("Evento Meta: MidiMetaEvent_Instrument Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_Marker)
				Registro::Depurar("Evento Meta: MidiMetaEvent_Marker Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_Cue)
				Registro::Depurar("Evento Meta: MidiMetaEvent_Cue Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_PatchName)
				Registro::Depurar("Evento Meta: MidiMetaEvent_PatchName Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));
			else if(i->second.MetaType() == MidiMetaEvent_DeviceName)
				Registro::Depurar("Evento Meta: MidiMetaEvent_DeviceName Contenido: " + i->second.Text() + " Largo: " + std::to_string(i->second.Text().length()));*/
		}
	}

	//NOTE probando la entrada midi
	while(m_configuracion->dispositivo_entrada() != NULL && m_configuracion->dispositivo_entrada()->KeepReading())
	{
		//Leer todos los eventos
		MidiEvent evento = m_configuracion->dispositivo_entrada()->Read();
		evento.SetChannel(1);
		evento.SetVelocity(120);

		if(m_configuracion->dispositivo_salida() != NULL)
			m_configuracion->dispositivo_salida()->Write(evento);

		//Almacena las notas tocadas por el jugador
		//Almacena la notas cuando recive el evento NoteOn
		if(evento.Type() == MidiEventType_NoteOn)
			m_notas_tocadas.insert(evento.NoteNumber());
		//Elimina las notas cuando recive el evento NoteOff
		else if(evento.Type() == MidiEventType_NoteOff)
			m_notas_tocadas.erase(evento.NoteNumber());
	}

	//Establece el color en gris para las notas tocadas por el jugador
	//Sera sobreescrito por el tablero de notas en la etapa de dibujo si la nota tocada es correcta
 	for(unsigned int id_nota : m_notas_tocadas)
 		m_teclas_activas->at(id_nota) = Color(0.7f, 0.7f, 0.7f);

	//Si selecciono un nuevo tiempo en la barra de progreso, se cambia la posicion.
	microseconds_t cambio_tiempo = m_barra->tiempo_seleccionado();
	if(cambio_tiempo >= 0)
	{
		m_musica->musica()->GoTo(cambio_tiempo);
		m_tablero->reiniciar();
		if(m_configuracion->dispositivo_salida() != NULL)
			m_configuracion->dispositivo_salida()->Reset();
	}

	//Cambio de velocidad de la musica
	if(m_cambio_velocidad)
	{
		m_cambio_velocidad = false;
		m_texto_velocidad.texto(std::to_string(static_cast<int>(m_velocidad_musica*100)) + "%");
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
	if(m_mostrar_subtitulo && m_subtitulo_texto.length() > 0)
	{
		//Dibuja el fondo
		m_textura_subtitulo->activar();
		m_rectangulo->textura(true);
		m_rectangulo->extremos_fijos(true, true);
		m_rectangulo->color(Color(0.9f, 0.9f, 0.9f));
		m_rectangulo->dibujar_estirable(Pantalla::Centro_horizontal()-((m_subtitulos.largo_texto()+40)/2), 90, m_subtitulos.largo_texto()+40, m_subtitulos.alto_texto()+20, 15.0f, 12.0f);
		m_subtitulos.dibujar();
		m_rectangulo->extremos_fijos(false, false);
	}
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
		m_configuracion->escribir("tipo_teclado", m_teclado_actual.texto());
	if(m_guardar_estado_subtitulo)
	{
		if(m_mostrar_subtitulo)
			m_configuracion->escribir("estado_subtitulo", "activo");
		else
			m_configuracion->escribir("estado_subtitulo", "inactivo");
	}
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
	bool cambio_teclado = false;
	if(tecla == TECLA_ESCAPE && !estado)
	{
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
	else if(tecla == TECLA_F4 && estado)
	{
		m_mostrar_subtitulo = !m_mostrar_subtitulo;
		m_guardar_estado_subtitulo = !m_guardar_estado_subtitulo;
		//Actualiza el subtitulo
		if(m_mostrar_subtitulo)
			m_subtitulos.texto(m_subtitulo_texto);
	}
	else if(tecla == TECLA_F5 && estado)
	{
		m_teclado_actual.cambiar(48, 37);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_F6 && estado)
	{
		m_teclado_actual.cambiar(36, 49);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_F7 && estado)
	{
		m_teclado_actual.cambiar(36, 61);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_F8 && estado)
	{
		m_teclado_actual.cambiar(28, 76);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_F9 && estado)
	{
		m_teclado_actual.cambiar(21, 88);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_INSERTAR && estado)
	{
		m_teclado_actual.tecla_inicial(m_teclado_actual.tecla_inicial()+1);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_SUPRIMIR && estado)
	{
		m_teclado_actual.tecla_inicial(m_teclado_actual.tecla_inicial()-1);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_REPAG && estado)
	{
		m_teclado_actual.numero_teclas(m_teclado_actual.numero_teclas()+1);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_AVPAG && estado)
	{
		m_teclado_actual.numero_teclas(m_teclado_actual.numero_teclas()-1);
		cambio_teclado = true;
	}
	else if(tecla == TECLA_INICIO && estado)
	{
		//Va al inicio de la canción
		m_musica->reiniciar(2000000);
		m_tablero->reiniciar();
		if(m_configuracion->dispositivo_salida() != NULL)
			m_configuracion->dispositivo_salida()->Reset();
	}
	if(cambio_teclado)
	{
		m_organo->calcular_tamannos();
		//El organo puede cambiar de tamaño al cambiar el numero de teclas, entonces hay que
		//ajustar el tamaño del tablero de notas
		m_tablero->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto()+40));
		m_guardar_tipo_teclado = true;
	}
}

void VentanaOrgano::evento_pantalla(float ancho, float alto)
{
	m_barra->dimension(ancho, m_barra->alto());
	m_organo->posicion(m_organo->x(), alto);
	m_organo->dimension(ancho, m_organo->alto());
	m_tablero->dimension(ancho, alto - (m_organo->alto() + m_barra->alto()+40));
	m_titulo_musica->dimension(Pantalla::Ancho, Pantalla::Alto - (m_organo->alto() + m_barra->alto() + 40));

	m_texto_velocidad.dimension(ancho, 40);
	m_texto_pausa.dimension(ancho, 40);
	m_subtitulos.dimension(Pantalla::Ancho, 20);
}
