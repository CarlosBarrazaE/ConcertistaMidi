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

	//https://en.cppreference.com/w/cpp/filesystem/directory_entry
	int i=0;
	for(const std::filesystem::directory_entry & elemento : std::filesystem::directory_iterator("../musica/"))
	{
		ruta_archivos.push_back(elemento.path());
		// + " Tamaño: " + std::to_string(elemento.file_size())
		std::vector<std::string> fila_nueva;
		fila_nueva.push_back(elemento.path());
		if(!elemento.is_directory())
			fila_nueva.push_back(std::to_string(elemento.file_size()));
		else
			fila_nueva.push_back("Carpeta");
		fila_nueva.push_back("35");
		fila_nueva.push_back("12/04/2020");
		m_tabla_archivos.insertar_fila(fila_nueva);
		i++;
	}

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

bool VentanaSeleccionMusica::abrir_archivo_seleccionado()
{
	int seleccion_actual = m_tabla_archivos.obtener_seleccion();
	if(seleccion_actual < ruta_archivos.size())
	{
		Registro::Nota("Abriendo archivo: " + ruta_archivos[seleccion_actual]);
		m_musica->cargar_midi(ruta_archivos[seleccion_actual]);
		m_musica->nombre_musica(ruta_archivos[seleccion_actual]);
		m_musica->autor("Autor");
		return true;
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
