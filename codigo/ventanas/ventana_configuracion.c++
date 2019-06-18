#include "ventana_configuracion.h++"

VentanaConfiguracion::VentanaConfiguracion(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.8, 0.9, 1.0);

	boton_atras = new Boton(10, 10, 100, 40, "Atras", textura, color, false, recursos);
}

VentanaConfiguracion::~VentanaConfiguracion()
{
	delete boton_atras;
}

void VentanaConfiguracion::actualizar(Raton *raton)
{
	boton_atras->actualizar(raton);
	if(boton_atras->esta_activado())
		this->accion = CambiarATitulo;
}

void VentanaConfiguracion::dibujar()
{
	boton_atras->dibujar();
}
