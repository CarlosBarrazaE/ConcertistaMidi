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
	return m_accion;
}
