#include "raton.h++"

Raton::Raton()
{
	m_posicion_x = 0;
	m_posicion_y = 0;
	m_desplazamiento_x = 0;
	m_desplazamiento_y = 0;
	m_boton_izquierdo = false;
	m_boton_central = false;
	m_boton_derecho = false;
	m_numero_clics = 0;
}

void Raton::actualizar_boton(BotonRaton boton, bool estado, int numero_clics)
{
	if(boton == BotonIzquierdo)
		m_boton_izquierdo = estado;
	else if(boton == BotonCentral)
		m_boton_central = estado;
	else if(boton == BotonDerecho)
		m_boton_derecho = estado;

	m_numero_clics = numero_clics;

	m_desplazamiento_x = 0;
	m_desplazamiento_y = 0;
}

void Raton::actualizar_posicion(int x, int y)
{
	m_posicion_x = x;
	m_posicion_y = y;
}

void Raton::actualizar_desplazamiento(int desplazamiento_x, int desplazamiento_y)
{
	m_desplazamiento_x = desplazamiento_x;
	m_desplazamiento_y = desplazamiento_y;
}

bool Raton::activado(BotonRaton boton)
{
	if(boton == BotonIzquierdo)
		return m_boton_izquierdo;
	else if(boton == BotonCentral)
		return m_boton_central;
	else if(boton == BotonDerecho)
		return m_boton_derecho;
	return false;
}

BotonRaton Raton::boton_activado()
{
	if(m_boton_izquierdo)
		return BotonIzquierdo;
	else if(m_boton_central)
		return BotonCentral;
	else if(m_boton_derecho)
		return BotonDerecho;
	return Ninguno;
}

int Raton::numero_clics()
{
	return m_numero_clics;
}

int Raton::x()
{
	return m_posicion_x;
}

int Raton::y()
{
	return m_posicion_y;
}

int Raton::dx()
{
	int desplazamiento = m_desplazamiento_x;
	m_desplazamiento_x = 0;
	return desplazamiento;
}

int Raton::dy()
{
	int desplazamiento = m_desplazamiento_y;
	m_desplazamiento_y = 0;
	return desplazamiento;
}
