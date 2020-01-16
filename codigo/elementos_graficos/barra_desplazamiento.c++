#include "barra_desplazamiento.h++"
#include "../registro.h++"
Barra_Desplazamiento::Barra_Desplazamiento(int x, int y, int ancho, int alto, int columna, int fila, int margen_columna, int margen_fila, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	m_columna = columna;
	m_fila = fila;
	m_margen_columna = margen_columna;
	m_margen_fila = margen_fila;
	m_ancho_actual = 0;
	m_alto_actual = 0;
	m_desplazamiento_x = 0;
	m_desplazamiento_y = 0;

	m_calcular_posicion = true;

	m_rectangulo = recursos->obtener_figura(F_Rectangulo);
	m_barra = recursos->obtener_textura(T_Barra);

	m_sobre_barra = false;
	m_boton_activado = false;
	m_proporcion = 0;
}

Barra_Desplazamiento::~Barra_Desplazamiento()
{
	for(Elemento* e : m_elementos)
		delete e;
	m_elementos.clear();

}

void Barra_Desplazamiento::agregar_elemento(Elemento *e)
{
	m_elementos.push_back(e);
}

void Barra_Desplazamiento::dimension(int ancho, int alto)
{
	this->ancho(ancho);
	this->alto(alto);
	m_calcular_posicion = true;
}

void Barra_Desplazamiento::actualizar(unsigned int diferencia_tiempo)
{
	if(m_calcular_posicion)
		this->actualizar_dimension();
	for(int i=0; i<m_elementos.size(); i++)
	{
		m_elementos[i]->actualizar(diferencia_tiempo);
	}
}

void Barra_Desplazamiento::dibujar()
{
	Elemento *e;
	for(int i=0; i<m_elementos.size(); i++)
	{
		e = m_elementos.at(i);
		if(e->posicion_y() + e->alto() > this->posicion_y() && e->posicion_y() < this->posicion_y() + this->alto() &&
			e->posicion_x() + e->ancho() > this->posicion_x() && e->posicion_x() < this->posicion_x() + this->ancho())
		{
			e->dibujar();
		}
	}
	m_rectangulo->textura(false);
	m_rectangulo->color(Color(0.95f, 0.95f, 0.95f));
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y(), this->ancho(), m_margen_fila);
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y()+this->alto()-m_margen_fila, this->ancho(), m_margen_fila);

	if(this->alto() < m_alto_actual)
	{
		m_barra->activar();
		m_rectangulo->extremos_fijos(false, true);
		m_rectangulo->textura(true);
		m_rectangulo->color(Color(0.7f, 0.7f, 0.7f));
		m_rectangulo->dibujar_estirable(this->posicion_x()+this->ancho()-10, this->posicion_y()+10, 10, this->alto()-20, 0, 10);
		m_rectangulo->color(Color(0.5f, 0.5f, 0.5f));
		m_rectangulo->dibujar_estirable(this->posicion_x()+this->ancho()-10, this->posicion_y()+10-m_desplazamiento_y*m_proporcion, 10, this->alto() * m_proporcion, 0, 10);
		m_rectangulo->extremos_fijos(false, false);
	}
}

void Barra_Desplazamiento::evento_raton(Raton *raton)
{
	int dy = raton->dy();
	int desplazamiento_nuevo_y = 0;
	int desplazamiento_anterior_y = 0;
	if(this->alto() < m_alto_actual)
	{
		desplazamiento_anterior_y = m_desplazamiento_y;
		if(dy != 0)
		{
			m_desplazamiento_y += dy*20;
		}
		else if(raton->x() >= this->posicion_x()+this->ancho()-10 && raton->x() <= this->posicion_x()+this->ancho() &&
		raton->y() >= this->posicion_y()+10 && raton->y() <= this->posicion_y() + this->alto()-20)
		{
			if(raton->activado(BotonIzquierdo) && m_sobre_barra)
			{
				m_boton_activado = true;
				//El inicio de la barra esta en this->posicion_y() + 20, el centro de la barra desplazable esta en (this->alto() * m_proporcion) / 2)
				m_desplazamiento_y = -(raton->y() - (this->posicion_y() + 20 + (this->alto() * m_proporcion) / 2)) / m_proporcion;
			}
			else if(!raton->activado(BotonIzquierdo))
			{
				m_sobre_barra = true;
			}
		}
		else if(m_boton_activado)
		{
			m_desplazamiento_y = -(raton->y() - (this->posicion_y() + 20 + (this->alto() * m_proporcion) / 2)) / m_proporcion;
		}
		else
		{
			m_sobre_barra = false;
		}

		if(!raton->activado(BotonIzquierdo) && m_boton_activado)
		{
			m_boton_activado = false;
		}

		if(m_desplazamiento_y > 0)
				m_desplazamiento_y = 0;
		else if(m_desplazamiento_y < this->alto() - m_alto_actual)
			m_desplazamiento_y = this->alto() - m_alto_actual;

		desplazamiento_nuevo_y = m_desplazamiento_y - desplazamiento_anterior_y;
	}

	for(int i=0; i<m_elementos.size(); i++)
	{
		if(this->alto() < m_alto_actual)
			m_elementos[i]->posicion_y(m_elementos[i]->posicion_y() + desplazamiento_nuevo_y);
		m_elementos[i]->evento_raton(raton);
	}
}

void Barra_Desplazamiento::evento_pantalla(int ancho, int alto)
{
}

void Barra_Desplazamiento::actualizar_dimension()
{
	int numero_columnas = this->ancho() / (m_columna + m_margen_columna);
	m_ancho_actual = (numero_columnas * m_columna) + ((numero_columnas - 1) * m_margen_columna);
	int x_inicio = (this->ancho() - m_ancho_actual) / 2 + this->posicion_x();
	int x_actual = x_inicio;
	int y_actual = this->posicion_y() + m_margen_fila;
	int contador_columnas = 1;
	for(int i=0; i<m_elementos.size(); i++)
	{
		m_elementos[i]->posicion_x(x_actual);
		m_elementos[i]->posicion_y(y_actual);

		if(contador_columnas < numero_columnas)
		{
			x_actual += m_columna + m_margen_columna;
		}
		else
		{
			contador_columnas = 0;
			x_actual = x_inicio;
			if(i<m_elementos.size()-1)
				y_actual += m_fila + m_margen_fila;
		}
		contador_columnas++;
	}
	m_alto_actual = y_actual + m_fila + m_margen_fila - this->posicion_y();

	m_desplazamiento_y = 0;
	m_calcular_posicion = false;
	if(this->alto() < m_alto_actual)
		m_proporcion = (double)(this->alto()-20) / (double)m_alto_actual;
}
