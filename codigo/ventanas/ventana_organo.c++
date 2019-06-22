#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, Teclas88, recursos);
}

VentanaOrgano::~VentanaOrgano()
{

}

void VentanaOrgano::actualizar(Raton *raton)
{
	organo->actualizar_y(Pantalla::alto);
	organo->actualizar_ancho(Pantalla::ancho);
	organo->actualizar(raton);
}

void VentanaOrgano::dibujar()
{
	organo->dibujar();
}
