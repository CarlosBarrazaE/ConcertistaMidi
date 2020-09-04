#include "elemento.h++"

Elemento::Elemento(int x, int y, int ancho, int alto)
{
	m_x = x;
	m_y = y;
	m_ancho = ancho;
	m_alto = alto;
	m_centrado = false;
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
}

Elemento::~Elemento()
{
}

void Elemento::_posicion(int x, int y)
{
	if(m_centrado)
		m_x = x - (m_ancho / 2);
	else
		m_x = x;
	m_y = y;
}

void Elemento::_dimension(int ancho, int alto)
{
	m_ancho = ancho;
    if(m_centrado)
		m_x = m_x - (m_ancho / 2);
	else
		m_x = m_x;

	m_alto = alto;
}

void Elemento::_centrado(bool centrado)
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
	this->_posicion(x, y);
}

void Elemento::dimension(int ancho, int alto)
{
	this->_dimension(ancho, alto);
}

void Elemento::centrado(bool centrado)
{
	this->_centrado(centrado);
}

int Elemento::x()
{
	return m_x;
}

int Elemento::y()
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
