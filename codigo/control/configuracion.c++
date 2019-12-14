#include "configuracion.h++"

Configuracion::Configuracion()
{
	m_entrada = new MidiCommIn(0);
	m_salida = new MidiCommOut(0);
}

Configuracion::Configuracion(unsigned int id_entrada, unsigned int id_salida)
{
	m_entrada = new MidiCommIn(id_entrada);
	m_salida = new MidiCommOut(id_salida);
}

Configuracion::~Configuracion()
{
}

void Configuracion::cambiar_entrada(unsigned int id_entrada)
{
	m_entrada = new MidiCommIn(id_entrada);
}

void Configuracion::cambiar_salida(unsigned int id_salida)
{
	m_salida = new MidiCommOut(id_salida);
}

MidiCommIn *Configuracion::o_entrada()
{
	return m_entrada;
}

MidiCommOut *Configuracion::o_salida()
{
	return m_salida;
}
