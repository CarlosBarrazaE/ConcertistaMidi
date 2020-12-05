#include "ventana.h++"

Ventana::Ventana()
{
	m_accion = Ninguna;
}

Ventana::~Ventana()
{
}

Accion Ventana::obtener_accion()
{
	Accion accion = m_accion;
	m_accion = Ninguna;
	return accion;
}
