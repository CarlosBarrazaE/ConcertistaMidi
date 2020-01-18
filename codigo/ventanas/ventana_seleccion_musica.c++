#include "ventana_seleccion_musica.h++"

VentanaSeleccionMusica::VentanaSeleccionMusica(Administrador_Recursos *recursos) : Ventana(), m_texto_titulo(recursos)
{
	m_rectangulo = recursos->obtener_figura(F_Rectangulo);
	Tipografia *texto_boton = recursos->obtener_tipografia(LetraChica);

	m_boton_atras = new Boton(10, Pantalla::Alto - 32, 120, 25, "Atrás", recursos);
	m_boton_atras->color_boton(Color(0.9f, 0.9f, 0.9f));
	m_boton_atras->tipografia(texto_boton);

	m_boton_continuar = new Boton(Pantalla::Ancho - 130, Pantalla::Alto - 32, 120, 25, "Continuar", recursos);
	m_boton_continuar->color_boton(Color(0.9f, 0.9f, 0.9f));
	m_boton_continuar->tipografia(texto_boton);

	m_texto_titulo.texto("Seleccione una canción para tocar");
	m_texto_titulo.tipografia(recursos->obtener_tipografia(LetraTitulo));
	m_texto_titulo.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_titulo.posicion(0, 0);
	m_texto_titulo.dimension(Pantalla::Ancho, 40);
	m_texto_titulo.centrado(true);
}

VentanaSeleccionMusica::~VentanaSeleccionMusica()
{
	delete m_boton_atras;
	delete m_boton_continuar;
}

void VentanaSeleccionMusica::actualizar(unsigned int diferencia_tiempo)
{
	m_boton_atras->actualizar(diferencia_tiempo);
	m_boton_continuar->actualizar(diferencia_tiempo);
}

void VentanaSeleccionMusica::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(0, 0, Pantalla::Ancho, 40, Color(0.141f, 0.624f, 0.933f));
	m_rectangulo->dibujar(0, Pantalla::Alto - 40, Pantalla::Ancho, 40, Color(0.761f, 0.887f, 0.985f));
	m_texto_titulo.dibujar();

	m_boton_atras->dibujar();
	m_boton_continuar->dibujar();
}

void VentanaSeleccionMusica::evento_raton(Raton *raton)
{
	m_boton_atras->evento_raton(raton);
	m_boton_continuar->evento_raton(raton);

	if(m_boton_atras->esta_activado())
		m_accion = CambiarATitulo;
	else if(m_boton_continuar->esta_activado())
		m_accion = CambiarASeleccionPista;
}

void VentanaSeleccionMusica::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		m_accion = CambiarATitulo;
	else if(tecla == TECLA_ENTRAR && !estado)
		m_accion = CambiarASeleccionPista;
}

void VentanaSeleccionMusica::evento_pantalla(int ancho, int alto)
{
	m_boton_atras->posicion_y(alto - 32);

	m_boton_continuar->posicion_x(ancho - 130);
	m_boton_continuar->posicion_y(alto - 32);

	m_boton_atras->evento_pantalla(ancho, alto);
	m_boton_continuar->evento_pantalla(ancho, alto);

	m_texto_titulo.dimension(Pantalla::Ancho, 40);
}
