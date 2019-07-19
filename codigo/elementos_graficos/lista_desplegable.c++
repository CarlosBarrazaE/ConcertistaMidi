#include "lista_desplegable.h++"

Lista_Desplegable::Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, Texto *texto, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->iniciar(recursos);
	this->centrado = false;
	this->ancho_icono = 0;
	this->alto_icono = 0;

	this->opciones = opciones;
	this->texto = texto;
	this->usar_iconos = false;
	this->centrado_vertical = (this->alto - this->texto->alto_texto()) / 2;
}

Lista_Desplegable::Lista_Desplegable(int x, int y, int ancho, int alto, int ancho_icono, int alto_icono, bool centrado, std::vector<std::string> opciones, std::vector<Textura2D*> iconos, Texto *texto, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->iniciar(recursos);
	this->ancho_icono = ancho_icono;
	this->alto_icono = alto_icono;
	this->centrado = centrado;

	this->opciones = opciones;
	this->iconos = iconos;
	this->texto = texto;

	if(this->opciones.size() != this->iconos.size())
		this->usar_iconos = false;
	else
		this->usar_iconos = true;

	if(this->usar_iconos)
	{
		if(this->centrado)
		{
			this->ajuste_icono = (this->ancho - this->ancho_icono)/2;
			this->centrado_vertical = (this->alto - (this->alto_icono + this->texto->alto_texto() + 2)) / 2;
			this->ajuste_texto = this->texto->ancho_texto(this->opciones[this->opcion_actual]) / 2;
		}
		else
		{
			this->centrado_vertical = (this->alto - (std::max(this->alto_icono, this->texto->alto_texto()))) / 2;
		}
	}
	else
	{
		this->centrado_vertical = (this->alto - this->texto->alto_texto()) / 2;
	}
}

Lista_Desplegable::~Lista_Desplegable()
{

}

void Lista_Desplegable::iniciar(Administrador_Recursos *recursos)
{
	this->opcion_actual = 0;
	this->ajuste_icono = 0;
	this->ajuste_texto = 0;
	this->centrado_vertical = 0;
	this->mostrar_lista = true;
	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
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
	if(this->usar_iconos)
	{
		this->rectangulo->textura(true);
		this->iconos[this->opcion_actual]->activar();
		this->rectangulo->dibujar(this->x+this->dx+this->ajuste_icono, this->y+this->dy+this->centrado_vertical, this->ancho_icono, this->alto_icono, Color(1.0f, 1.0f, 1.0f));

		if(centrado)
			this->texto->imprimir(this->x+this->dx+(this->ancho/2)-this->ajuste_texto, this->y+this->dy+this->centrado_vertical+this->alto_icono+this->texto->alto_texto()+2, this->opciones[this->opcion_actual], Color(1.0f, 1.0f, 1.0f));
		else
			this->texto->imprimir(this->x+this->dx+this->ancho_icono + 2, this->y+this->dy+this->centrado_vertical+this->alto_icono, this->opciones[this->opcion_actual], Color(1.0f, 1.0f, 1.0f));
	}
	else
	{
		this->texto->imprimir(this->x+this->dx+2, this->y+this->dy+this->centrado_vertical+this->texto->alto_texto(), this->opciones[this->opcion_actual], Color(1.0f, 1.0f, 1.0f));
	}
	if(this->mostrar_lista)
	{
	}
}

void Lista_Desplegable::evento_raton(Raton *raton)
{
}
