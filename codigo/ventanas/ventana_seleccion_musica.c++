#include "ventana_seleccion_musica.h++"

VentanaSeleccionMusica::VentanaSeleccionMusica(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana(), m_texto_titulo(recursos), m_tabla_archivos(10, 50, Pantalla::Ancho-20, Pantalla::Alto-100, recursos)
{
	m_configuracion = configuracion;
	m_musica = musica;

	m_rectangulo = recursos->figura(F_Rectangulo);

	m_boton_atras = new Boton(10, Pantalla::Alto - 32, 120, 25, "Atrás", LetraChica, recursos);
	m_boton_atras->color_boton(Color(0.9f, 0.9f, 0.9f));

	m_boton_continuar = new Boton(Pantalla::Ancho - 130, Pantalla::Alto - 32, 120, 25, "Continuar", LetraChica, recursos);
	m_boton_continuar->color_boton(Color(0.9f, 0.9f, 0.9f));

	m_texto_titulo.texto("Seleccione una canción para tocar");
	m_texto_titulo.tipografia(recursos->tipografia(LetraTitulo));
	m_texto_titulo.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_titulo.posicion(0, 0);
	m_texto_titulo.dimension(Pantalla::Ancho, 40);
	m_texto_titulo.centrado(true);

	//Fila titulo
	m_tabla_archivos.agregar_columna("Nombre Archivo", 0.7);
	m_tabla_archivos.agregar_columna("Tamaño", 0.1);
	m_tabla_archivos.agregar_columna("Veces", 0.1);
	m_tabla_archivos.agregar_columna("Fecha", 0.1);

	//Falta guardar la pila de rutas anteriores
	std::string ultima_carpeta_activa = m_configuracion->leer("ultima_carpeta_activa");
	if(ultima_carpeta_activa != "" && std::ifstream(ultima_carpeta_activa))//Verifica que la carpeta aun exista
	{
		this->cargar_carpeta(ultima_carpeta_activa, true);
	}
	else
		this->cargar_carpeta("../musica", true);
}

VentanaSeleccionMusica::~VentanaSeleccionMusica()
{
	delete m_boton_atras;
	delete m_boton_continuar;
}

void VentanaSeleccionMusica::actualizar(unsigned int diferencia_tiempo)
{
	m_tabla_archivos.actualizar(diferencia_tiempo);
	m_boton_atras->actualizar(diferencia_tiempo);
	m_boton_continuar->actualizar(diferencia_tiempo);
}

void VentanaSeleccionMusica::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(0, 0, Pantalla::Ancho, 40, Color(0.141f, 0.624f, 0.933f));
	m_rectangulo->dibujar(0, Pantalla::Alto - 40, Pantalla::Ancho, 40, Color(0.761f, 0.887f, 0.985f));
	m_texto_titulo.dibujar();

	m_tabla_archivos.dibujar();

	m_boton_atras->dibujar();
	m_boton_continuar->dibujar();
}

void VentanaSeleccionMusica::cargar_carpeta(std::string ruta_abrir, bool guardar_ruta)
{
	//La primera vez no se guarda la base de datos porque se acaba de leer
	if(m_rutas.size() > 0)
		m_configuracion->escribir("ultima_carpeta_activa", ruta_abrir);
	if(guardar_ruta)
		m_rutas.push_back(ruta_abrir);//Para guardar solo cuando va hacia delante y no cuando se retrocede
	for(const std::filesystem::directory_entry elemento : std::filesystem::directory_iterator(ruta_abrir))
	{
		std::string ruta = std::string(elemento.path());
		unsigned int inicio_archivo = 0;
		unsigned int extencion = ruta.length()-1;
		//Se recorre la ruta desde el final
		bool encontrado = false;
		for(unsigned int i=ruta.length()-1; i>0 && !encontrado; i--)
		{
			//Se busca el punto solo si es un archivo
			if(!elemento.is_directory() && extencion == ruta.length()-1 && ruta[i] == '.')
			{
				//Encuentra el primer punto
				extencion = i;
			}

			if(inicio_archivo == 0 && ruta[i] == '/')
			{
				//Termina al encontrar el inicio del nombre del archivo
				inicio_archivo = i;
				encontrado = true;
				i=0;
			}
		}

		//Se obtiene el nombre y la extencion del archivo
		std::string nombre_archivo, extencion_archivo;
		if(extencion != ruta.length()-1)
		{
			nombre_archivo = ruta.substr(inicio_archivo+1, extencion-(inicio_archivo+1));
			extencion_archivo = ruta.substr(extencion+1);
		}
		else
			nombre_archivo = ruta.substr(inicio_archivo+1);
		std::replace(nombre_archivo.begin(), nombre_archivo.end(), '_', ' ');//Reemplaza el guion bajo por espacio

		bool es_midi = false;
		if(extencion_archivo == "mid" ||
			extencion_archivo == "MID" ||
			extencion_archivo == "midi" ||
			extencion_archivo == "MIDI"
		)
		{
			es_midi = true;
		}

		if(elemento.is_directory() || (!elemento.is_directory() && es_midi))
		{
			Datos_Archivos actual;
			actual.es_carpeta = elemento.is_directory();
			actual.ruta = elemento.path();
			actual.nombre = nombre_archivo;

			if(!elemento.is_directory())
			{
				//Archivo
				actual.tamanno = elemento.file_size();
				actual.fecha = "Fecha_archivo";
			}
			//Todo Filtrar archivos Midi
			m_lista_archivos.push_back(actual);
		}
	}

	//Ordenar Lista
	std::sort(m_lista_archivos.begin(), m_lista_archivos.end());

	//Crear Tabla
	for(unsigned int i=0; i<m_lista_archivos.size(); i++)
	{
		std::vector<std::string> fila_nueva;

		fila_nueva.push_back(m_lista_archivos[i].nombre);
		fila_nueva.push_back(std::to_string(m_lista_archivos[i].tamanno));
		fila_nueva.push_back("35");
		fila_nueva.push_back(m_lista_archivos[i].fecha);
		m_tabla_archivos.insertar_fila(fila_nueva);
	}
}

bool VentanaSeleccionMusica::abrir_archivo_seleccionado()
{
	unsigned int seleccion_actual = m_tabla_archivos.obtener_seleccion();
	if(seleccion_actual < m_lista_archivos.size())
	{
		if(m_lista_archivos[seleccion_actual].es_carpeta)
		{
			std::string ruta_nueva = m_lista_archivos[seleccion_actual].ruta;

			//Limpia la lista y la tabla
			m_lista_archivos.clear();
			m_tabla_archivos.eliminar_contenido();

			//Carga la lista de archivos de la carpeta seleccionada
			Registro::Nota("Abriendo carpeta: " + ruta_nueva);
			this->cargar_carpeta(ruta_nueva, true);
			return false;
		}
		else
		{
			//Abre el archivo seleccionado
			Registro::Nota("Abriendo archivo: " + m_lista_archivos[seleccion_actual].ruta);
			m_musica->cargar_midi(m_lista_archivos[seleccion_actual].ruta);
			m_musica->nombre_musica(m_lista_archivos[seleccion_actual].nombre);
			m_musica->autor("Autor");
			return true;
		}
	}
	return false;
}

void VentanaSeleccionMusica::evento_raton(Raton *raton)
{
	m_tabla_archivos.evento_raton(raton);

	//Abrir el archivo con doble clic
	if(raton->activado(BotonIzquierdo) && raton->numero_clics() == 2)
	{
		if(this->abrir_archivo_seleccionado())
			m_accion = CambiarASeleccionPista;
	}

	m_boton_atras->evento_raton(raton);
	m_boton_continuar->evento_raton(raton);

	if(m_boton_atras->esta_activado())
		m_accion = CambiarATitulo;
	else if(m_boton_continuar->esta_activado())
	{
		if(this->abrir_archivo_seleccionado())
			m_accion = CambiarASeleccionPista;
	}
}

void VentanaSeleccionMusica::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		m_accion = CambiarATitulo;
	else if((tecla == TECLA_ENTRAR || tecla == TECLA_FLECHA_DERECHA) && !estado)
	{
		if(this->abrir_archivo_seleccionado())
			m_accion = CambiarASeleccionPista;
	}
	else if((tecla == TECLA_BORRAR || tecla == TECLA_FLECHA_IZQUIERDA) && !estado)
	{
		if(m_rutas.size() > 1)
		{
			m_lista_archivos.clear();
			m_tabla_archivos.eliminar_contenido();

			//Carga la lista de archivos de la carpeta seleccionada
			m_rutas.erase(m_rutas.end());//Borra el ultimo, para cargar el anterior
			Registro::Nota("Abriendo anterior: " + m_rutas[m_rutas.size()-1]);
			this->cargar_carpeta(m_rutas[m_rutas.size()-1], false);
		}
	}
	else if(tecla == TECLA_FLECHA_ABAJO && !estado)
		m_tabla_archivos.cambiar_seleccion(1);
	else if(tecla == TECLA_FLECHA_ARRIBA && !estado)
		m_tabla_archivos.cambiar_seleccion(-1);
}

void VentanaSeleccionMusica::evento_pantalla(int ancho, int alto)
{
	m_texto_titulo.dimension(Pantalla::Ancho, 40);

	m_tabla_archivos.dimension(ancho-20, alto-100);
	m_tabla_archivos.evento_pantalla(ancho, alto);

	m_boton_atras->y(alto - 32);
	m_boton_atras->evento_pantalla(ancho, alto);

	m_boton_continuar->posicion(ancho - 130, alto - 32);
	m_boton_continuar->evento_pantalla(ancho, alto);
}
