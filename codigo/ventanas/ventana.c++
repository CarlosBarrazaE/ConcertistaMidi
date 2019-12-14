#include "ventana.h++"

Ventana::Ventana()
{
	m_accion = Ninguna;
}

Accion Ventana::obtener_accion()
{
	return m_accion;
}
