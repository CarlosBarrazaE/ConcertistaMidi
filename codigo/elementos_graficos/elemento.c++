#include "elemento.h++"

Elemento::Elemento(float x, float y, float ancho, float alto)
{
	m_x = x;
	m_y = y;
	m_ancho = ancho;
	m_alto = alto;
	m_centrado = false;
}

Elemento::Elemento(float x, float y, float ancho, float alto, bool centrado)
{
	m_ancho = ancho;
	m_alto = alto;
	m_centrado = centrado;
	this->_posicion(x, y);
}

Elemento::~Elemento()
{
}

void Elemento::_posicion(float x, float y)
{
	if(m_centrado)
		m_x = x - (m_ancho / 2);
	else
		m_x = x;
	m_y = y;
}

void Elemento::_dimension(float ancho, float alto)
{
	m_ancho = ancho;
    if(m_centrado)
		m_x = m_x - (m_ancho / 2);

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

void Elemento::posicion(float x, float y)
{
	this->_posicion(x, y);
}

void Elemento::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
}

void Elemento::centrado(bool centrado)
{
	this->_centrado(centrado);
}

float Elemento::x()
{
	return m_x;
}

float Elemento::y()
{
	return m_y;
}

float Elemento::ancho()
{
	return m_ancho;
}

float Elemento::alto()
{
	return m_alto;
}
