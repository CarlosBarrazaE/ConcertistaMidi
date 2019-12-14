#include "elemento.h++"

Elemento::Elemento(int x, int y, int ancho, int alto)
{
	m_x = x;
	m_y = y;
	m_ancho = ancho;
	m_alto = alto;
	m_centrado = false;
	m_dx = 0;
	m_dy = 0;
}

Elemento::Elemento(int x, int y, int ancho, int alto, bool centrado)
{
	if(centrado)
		m_x = x - (m_ancho / 2);
	else
		m_x = x;

	m_y = y;
	m_ancho = ancho;
	m_alto = alto;
	m_centrado = centrado;
	m_dx = 0;
	m_dy = 0;
}

int Elemento::posicion_x()
{
	return m_x;
}

int Elemento::posicion_y()
{
	return m_y;
}

int Elemento::ancho()
{
	return m_ancho;
}

int Elemento::alto()
{
	return m_alto;
}

void Elemento::centrado(bool centrado)
{
	bool centrado_actual = m_centrado;
	m_centrado = centrado;
	if(m_centrado)
	{
		if(!centrado_actual)//Centra el objeto
			m_x = m_x - (m_ancho / 2);
	}
	else
	{
		if(centrado_actual)//Revierte el centrado
			m_x = m_x + (m_ancho / 2);
	}
}

void Elemento::posicion(int x, int y)
{
	if(m_centrado)
		m_x = x - (m_ancho / 2);
	else
		m_x = x;
	m_y = y;
}

void Elemento::posicion_x(int x)
{
	if(m_centrado)
		m_x = x - (m_ancho / 2);
	else
		m_x = x;
}

void Elemento::posicion_y(int y)
{
	m_y = y;
}

int Elemento::dx()
{
	return m_dx;
}

int Elemento::dy()
{
	return m_dy;
}

void Elemento::dimension(int ancho, int alto)
{
	m_ancho = ancho;
    if(m_centrado)
		m_x = m_x - (m_ancho / 2);
	else
		m_x = m_x;

	m_alto = alto;
}

void Elemento::ancho(int ancho)
{
	m_ancho = ancho;
    if(m_centrado)
		m_x = m_x - (m_ancho / 2);
	else
		m_x = m_x;
}

void Elemento::alto(int alto)
{
	m_alto = alto;
}

void Elemento::ajuste(int dx, int dy)
{
	m_dx = dx;
	m_dy = dy;
}

void Elemento::dx(int dx)
{
	m_dx = dx;
}

void Elemento::dy(int dy)
{
	m_dy = dy;
}
