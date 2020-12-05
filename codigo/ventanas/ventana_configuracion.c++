#include "ventana_configuracion.h++"

VentanaConfiguracion::VentanaConfiguracion(Configuracion *configuracion, Administrador_Recursos *recursos) : Ventana(), m_texto_titulo(recursos)
{
	m_configuracion = configuracion;

	m_rectangulo = recursos->figura(F_Rectangulo);

	m_texto_titulo.texto("Configuración");
	m_texto_titulo.tipografia(recursos->tipografia(LetraTitulo));
	m_texto_titulo.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_titulo.posicion(0, 0);
	m_texto_titulo.dimension(Pantalla::Ancho, 40);
	m_texto_titulo.centrado(true);

	m_boton_atras = new Boton(10, Pantalla::Alto - 32, 120, 25, "Atrás", LetraChica, recursos);
	m_boton_atras->color_boton(Color(0.9f, 0.9f, 0.9f));

	m_solapa = new Solapa(0, 40, 250, Pantalla::Alto, recursos);
	m_solapa->agregar_solapa("General");
	m_solapa1_titulo = new Etiqueta(250, 50, Pantalla::Ancho-250, 40, true, "General", LetraTitulo, recursos);
	m_solapa1_texto_restablecer = new Etiqueta(260, 100, Pantalla::Ancho-270, 25, false, "Volver a la configuración predeterminada", LetraChica, recursos);
	m_solapa1_texto_limpiar = new Etiqueta(260, 135, Pantalla::Ancho-270, 25, false, "Limpiar la base de datos", LetraChica, recursos);
	m_solapa1_texto_borrar = new Etiqueta(260, 170, Pantalla::Ancho-270, 25, false, "Borrar la base de datos", LetraChica, recursos);
	m_solapa1_restablecer = new Boton(Pantalla::Ancho - 110, 100, 100, 25, "Restablecer", LetraChica, recursos);
	m_solapa1_limpiar_bd = new Boton(Pantalla::Ancho - 110, 135, 100, 25, "Limpiar", LetraChica, recursos);
	m_solapa1_borrar_db = new Boton(Pantalla::Ancho - 110, 170, 100, 25, "Borrar", LetraChica, recursos);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_titulo);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_texto_restablecer);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_texto_limpiar);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_texto_borrar);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_restablecer);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_limpiar_bd);
	m_solapa->agregar_elemento_solapa(0, m_solapa1_borrar_db);

	m_solapa->agregar_solapa("Carpetas MIDI");
	m_solapa2_titulo = new Etiqueta(250, 50, Pantalla::Ancho-250, 40, true, "Carpetas MIDI", LetraTitulo, recursos);
	m_solapa->agregar_elemento_solapa(1, m_solapa2_titulo);

	m_solapa->agregar_solapa("Dispositivos");
	m_solapa3_titulo = new Etiqueta(250, 50, Pantalla::Ancho-250, 40, true, "Dispositivos", LetraTitulo, recursos);
	m_solapa->agregar_elemento_solapa(2, m_solapa3_titulo);

	m_solapa->agregar_solapa("Video");
	m_solapa4_titulo = new Etiqueta(250, 50, Pantalla::Ancho-250, 40, true, "Video", LetraTitulo, recursos);
	m_solapa4_casilla_pantalla_completa = new Casilla_Verificacion(260, 100, Pantalla::Ancho-270, 30, "Pantalla Completa (F11)", recursos);
	m_solapa->agregar_elemento_solapa(3, m_solapa4_titulo);
	m_solapa->agregar_elemento_solapa(3, m_solapa4_casilla_pantalla_completa);

	//Actualiza segun el estado de la pantalla
	if(m_solapa4_casilla_pantalla_completa->activado() != Pantalla::PantallaCompleta)
		m_solapa4_casilla_pantalla_completa->estado(Pantalla::PantallaCompleta);

	m_ultima_solapa = 0;
}

VentanaConfiguracion::~VentanaConfiguracion()
{
	delete m_boton_atras;

	delete m_solapa1_titulo;
	delete m_solapa1_texto_restablecer;
	delete m_solapa1_texto_limpiar;
	delete m_solapa1_texto_borrar;
	delete m_solapa1_restablecer;
	delete m_solapa1_limpiar_bd;
	delete m_solapa1_borrar_db;

	delete m_solapa2_titulo;
	delete m_solapa3_titulo;
	delete m_solapa4_titulo;
	delete m_solapa4_casilla_pantalla_completa;

	delete m_solapa;
}

void VentanaConfiguracion::actualizar(unsigned int diferencia_tiempo)
{
	m_solapa->actualizar(diferencia_tiempo);
}

void VentanaConfiguracion::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(0, 0, Pantalla::Ancho, 40, Color(0.141f, 0.624f, 0.933f));//Borde arriba
	m_rectangulo->dibujar(0, Pantalla::Alto - 40, Pantalla::Ancho, 40, Color(0.761f, 0.887f, 0.985f));//Borde abajo
	m_texto_titulo.dibujar();

	m_solapa->dibujar();
	m_boton_atras->dibujar();
}

void VentanaConfiguracion::evento_raton(Raton *raton)
{
	m_solapa->evento_raton(raton);
	m_boton_atras->evento_raton(raton);
	if(m_boton_atras->esta_activado())
		m_accion = CambiarATitulo;

	if(m_solapa1_restablecer->esta_activado())
	{
		m_configuracion->escribir("velocidad_musica", "1.000000");
		m_configuracion->escribir("duracion_nota", "6700");
		m_configuracion->escribir("tipo_teclado", "88");
		m_configuracion->escribir("estado_subtitulo", "activo");
		Notificacion::Nota("Configuración restablecida", 5);
	}
	if(m_solapa1_limpiar_bd->esta_activado())
	{
		Notificacion::Nota("Limpiando base de datos...", 1);
		unsigned int registros_eliminados = 0;
		std::vector<std::string> archivos = m_configuracion->base_de_datos()->lista_archivos();
		for(unsigned int x=0; x<archivos.size(); x++)
		{
			//Archivos que ya no existen, movidos o renombrados
			if(!std::ifstream(archivos[x]))
			{
				//NOTE Agregar las demas tablas una vez que esten implementadas
				m_configuracion->base_de_datos()->borrar_archivo(archivos[x]);
				Registro::Nota("El archivo no existe: " + archivos[x]);
				registros_eliminados++;
			}
		}
		if(registros_eliminados > 0)
			Notificacion::Nota("Se borraron "+std::to_string(registros_eliminados)+" registros huerfanos", 5);
		else
			Notificacion::Nota("Base de datos limpia", 5);
	}
	if(m_solapa1_borrar_db->esta_activado())
	{
		m_configuracion->base_de_datos()->borrar_archivos();
		Notificacion::Nota("Base de datos borrada", 5);
	}
	if(m_solapa4_casilla_pantalla_completa->cambio_estado())
	{
		if(m_solapa4_casilla_pantalla_completa->activado())
			m_accion = EntrarPantallaCompleta;
		else
			m_accion = SalirPantallaCompleta;
	}
}

void VentanaConfiguracion::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		m_accion = CambiarATitulo;

	if(m_solapa4_casilla_pantalla_completa->activado() != Pantalla::PantallaCompleta)
		m_solapa4_casilla_pantalla_completa->estado(Pantalla::PantallaCompleta);
}

void VentanaConfiguracion::evento_pantalla(float ancho, float alto)
{
	m_texto_titulo.dimension(ancho, 40);
	m_boton_atras->posicion(m_boton_atras->x(), alto - 32);

	m_solapa->dimension(250, alto);

	m_solapa1_titulo->dimension(Pantalla::Ancho-250, 40);
	m_solapa1_restablecer->posicion(Pantalla::Ancho - 110, 100);
	m_solapa1_limpiar_bd->posicion(Pantalla::Ancho - 110, 135);
	m_solapa1_borrar_db->posicion(Pantalla::Ancho - 110, 170);

	m_solapa2_titulo->dimension(Pantalla::Ancho-250, 40);

	m_solapa3_titulo->dimension(Pantalla::Ancho-250, 40);

	m_solapa4_titulo->dimension(Pantalla::Ancho-250, 40);
	m_solapa4_casilla_pantalla_completa->dimension(Pantalla::Ancho-270, 25);
}
