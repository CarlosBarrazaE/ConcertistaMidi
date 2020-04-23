#include "teclado_configuracion.h++"

Teclado_Configuracion::Teclado_Configuracion()
{
	//Teclado predeterminado de 88 teclas
	m_numero_blancas = 52;
	m_numero_negras = 36;
	m_inicio_blanca = 1;
	m_inicio_negra = 4;
	m_desplazamiento_blancas = 0;
	m_desplazamiento_negras = 0;
	m_primera_barra = 2;
	m_en_do_primera_barra = true;
}

Teclado_Configuracion::Teclado_Configuracion(int numero_b,int numero_n, int inicio_b, int inicio_n, int desplazamiento_b, int desplazamiento_n, int primera_barra, bool en_do_primera_barra)
{
	m_numero_blancas = numero_b;
	m_numero_negras = numero_n;
	m_inicio_blanca = inicio_b;
	m_inicio_negra = inicio_n;
	m_desplazamiento_blancas = desplazamiento_b;
	m_desplazamiento_negras = desplazamiento_n;
	m_primera_barra = primera_barra;
	m_en_do_primera_barra = en_do_primera_barra;
}

int Teclado_Configuracion::numero_blancas()
{
	return m_numero_blancas;
}

int Teclado_Configuracion::numero_negras()
{
	return m_numero_negras;
}

int Teclado_Configuracion::inicio_blancas()
{
	return m_inicio_blanca;
}

int Teclado_Configuracion::inicio_negras()
{
	return m_inicio_negra;
}

int Teclado_Configuracion::desplazamiento_blancas()
{
	return m_desplazamiento_blancas;
}

int Teclado_Configuracion::desplazamiento_negras()
{
	return m_desplazamiento_negras;
}

int Teclado_Configuracion::primera_barra()
{
	return m_primera_barra;
}

bool Teclado_Configuracion::en_do_primera_barra()
{
	return m_en_do_primera_barra;
}
