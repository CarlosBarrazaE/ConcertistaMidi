#include "ventana_seleccion_musica.h++"

VentanaSeleccionMusica::VentanaSeleccionMusica(Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana(), m_texto_titulo(recursos), m_tabla_archivos(10, 50, Pantalla::Ancho-20, Pantalla::Alto-100, recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);
	Tipografia *texto_boton = recursos->tipografia(LetraChica);

	m_boton_atras = new Boton(10, Pantalla::Alto - 32, 120, 25, "Atrás", recursos);
	m_boton_atras->color_boton(Color(0.9f, 0.9f, 0.9f));
	m_boton_atras->tipografia(texto_boton);

	m_boton_continuar = new Boton(Pantalla::Ancho - 130, Pantalla::Alto - 32, 120, 25, "Continuar", recursos);
	m_boton_continuar->color_boton(Color(0.9f, 0.9f, 0.9f));
	m_boton_continuar->tipografia(texto_boton);

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

	this->cargar_carpeta("../musica");

	m_musica = musica;
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

void VentanaSeleccionMusica::cargar_carpeta(std::string ruta_abrir)
{
	for(const std::filesystem::directory_entry elemento : std::filesystem::directory_iterator(ruta_abrir))
	{
		std::string ruta = std::string(elemento.path());
		int inicio_archivo = 0;
		int extencion = ruta.length()-1;
		//Se recorre la ruta desde el final
		for(int i=ruta.length()-1; i>0; i--)
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
			lista_archivos.push_back(actual);
		}
	}

	//Ordenar Lista

	//Crear Tabla
	for(int i=0; i<lista_archivos.size(); i++)
	{
		std::vector<std::string> fila_nueva;

		fila_nueva.push_back(lista_archivos[i].nombre);
		fila_nueva.push_back(std::to_string(lista_archivos[i].tamanno));
		fila_nueva.push_back("35");
		fila_nueva.push_back(lista_archivos[i].fecha);
		m_tabla_archivos.insertar_fila(fila_nueva);
	}
}

bool VentanaSeleccionMusica::abrir_archivo_seleccionado()
{
	int seleccion_actual = m_tabla_archivos.obtener_seleccion();
	if(seleccion_actual < lista_archivos.size())
	{
		if(lista_archivos[seleccion_actual].es_carpeta)
		{
			std::string ruta_nueva = lista_archivos[seleccion_actual].ruta;

			//Limpia la lista y la tabla
			lista_archivos.clear();
			m_tabla_archivos.eliminar_contenido();

			//Carga la lista de archivos de la carpeta seleccionada
			Registro::Nota("Abriendo carpeta: " + ruta_nueva);
			this->cargar_carpeta(ruta_nueva);
			return false;
		}
		else
		{
			//Abre el archivo seleccionado
			Registro::Nota("Abriendo archivo: " + lista_archivos[seleccion_actual].ruta);
			m_musica->cargar_midi(lista_archivos[seleccion_actual].ruta);
			m_musica->nombre_musica(lista_archivos[seleccion_actual].nombre);
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
	if(raton->activado(BotonIzquierdo) && raton->numero_clics() == 2 && m_tabla_archivos.obtener_seleccion() >= 0)
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
	else if(tecla == TECLA_ENTRAR && !estado)
	{
		if(this->abrir_archivo_seleccionado())
			m_accion = CambiarASeleccionPista;
	}
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
