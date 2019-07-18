#include "lista_desplegable.h++"

Lista_Desplegable::Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->opciones = opciones;
	this->usar_iconos = false;
	this->opcion_actual = 0;
}

Lista_Desplegable::Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, std::vector<Textura2D*> iconos, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->opciones = opciones;
	this->iconos = iconos;
	this->usar_iconos = true;
	this->opcion_actual = 0;
}

Lista_Desplegable::~Lista_Desplegable()
{
}

void Lista_Desplegable::opcion_predeterminada(unsigned int opcion)
{
	if(opcion >= 0 && opcion < opciones.size())
		this->opcion_actual = opcion;
}

unsigned int Lista_Desplegable::opcion_seleccionada()
{
	return this->opcion_actual;
}

void Lista_Desplegable::actualizar(unsigned int diferencia_tiempo)
{
}

void Lista_Desplegable::dibujar()
{
}

void Lista_Desplegable::evento_raton(Raton *raton)
{
}
