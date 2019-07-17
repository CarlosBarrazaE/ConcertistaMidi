#include "ventana_configuracion.h++"

VentanaConfiguracion::VentanaConfiguracion(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.8f, 0.9f, 1.0f);

	boton_atras = new Boton(10, 10, 100, 40, "Atrás", textura, color, false, recursos);
}

VentanaConfiguracion::~VentanaConfiguracion()
{
	delete boton_atras;
}

void VentanaConfiguracion::actualizar(unsigned int diferencia_tiempo)
{
	boton_atras->actualizar(diferencia_tiempo);
}

void VentanaConfiguracion::dibujar()
{
	boton_atras->dibujar();
}

void VentanaConfiguracion::evento_raton(Raton *raton)
{
	boton_atras->evento_raton(raton);
	if(boton_atras->esta_activado())
		this->accion = CambiarATitulo;
}

void VentanaConfiguracion::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		this->accion = CambiarATitulo;
}

void VentanaConfiguracion::evento_pantalla(int ancho, int alto)
{
}
