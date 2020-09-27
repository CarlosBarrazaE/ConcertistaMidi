#include "ventana_configuracion.h++"

VentanaConfiguracion::VentanaConfiguracion(Configuracion *configuracion, Administrador_Recursos *recursos) : Ventana()
{
	m_configuracion = configuracion;

	m_boton_atras = new Boton(10, 10, 100, 40, "Atrás", recursos);
	m_boton_atras->color_boton(Color(0.8f, 0.9f, 1.0f));
}

VentanaConfiguracion::~VentanaConfiguracion()
{
	delete m_boton_atras;
}

void VentanaConfiguracion::actualizar(unsigned int diferencia_tiempo)
{
	m_boton_atras->actualizar(diferencia_tiempo);
}

void VentanaConfiguracion::dibujar()
{
	m_boton_atras->dibujar();
}

void VentanaConfiguracion::evento_raton(Raton *raton)
{
	m_boton_atras->evento_raton(raton);
	if(m_boton_atras->esta_activado())
		m_accion = CambiarATitulo;
}

void VentanaConfiguracion::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		m_accion = CambiarATitulo;
}

void VentanaConfiguracion::evento_pantalla(float /*ancho*/, float /*alto*/)
{
}
