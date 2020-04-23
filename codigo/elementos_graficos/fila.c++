#include "fila.h++"
Fila::Fila(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_color_fondo(0.95f, 0.95f, 0.95f)
{
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_sobre_boton = false;
	m_boton_pre_activado = false;
	m_boton_seleccionado = false;

	m_color_actual = m_color_fondo;
	m_color_seleccion = Color(m_color_fondo.rojo()-0.05f, m_color_fondo.verde()-0.05f, m_color_fondo.azul()-0.05f);
}

Fila::~Fila()
{
}

void Fila::actualizar(unsigned int diferencia_tiempo)
{
	if(m_boton_seleccionado)
		m_color_actual = m_color_seleccion;
	else
		m_color_actual = m_color_fondo;

	if(m_sobre_boton)
		m_color_actual = Color(m_color_actual.rojo()-0.08f, m_color_actual.verde()-0.08f, m_color_actual.azul()-0.08f);
}

void Fila::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x()+this->dx(), this->y()+this->dy(), this->ancho(), this->alto(), m_color_actual);
	for(int x=0; x<m_celda.size(); x++)
	{
		m_rectangulo->dibujar(m_celda.at(x)->x(), m_celda.at(x)->y(), 10, 40, Color(0.4f, 0.2f, 0.4f));
		m_celda.at(x)->dibujar();
	}
}

void Fila::evento_raton(Raton *raton)
{
	if(raton->x() >= this->x()+this->dx() && raton->x() <= this->x()+this->dx() + this->ancho() &&
		raton->y() >= this->y()+this->dy() && raton->y() <= this->y()+this->dy() + this->alto())
	{
		if(raton->activado(BotonIzquierdo) && m_sobre_boton)
			m_boton_pre_activado = true;
		else if(!raton->activado(BotonIzquierdo))
		{
			m_sobre_boton = true;
			if(m_boton_pre_activado)
			{
				m_boton_seleccionado = true;
				m_boton_pre_activado = false;
			}
		}
	}
	else
	{
		m_sobre_boton = false;
		m_boton_pre_activado = false;
	}
}

void Fila::evento_pantalla(int ancho, int alto)
{

}

void Fila::agregar_celda(Etiqueta *celda)
{
	m_celda.push_back(celda);
}

bool Fila::esta_seleccionado()
{
	return m_boton_seleccionado;
}

void Fila::deseleccionar()
{
	m_boton_seleccionado = false;
}
