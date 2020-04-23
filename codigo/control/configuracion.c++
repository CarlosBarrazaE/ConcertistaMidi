#include "configuracion.h++"

Configuracion::Configuracion()
{
	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();

	m_cantidad_dispositivos_entrada = dispositivos_entrada.size();
	m_cantidad_dispositivos_salida = dispositivos_salida.size();

	this->cambiar_entrada(0);
	this->cambiar_salida(0);
}

Configuracion::Configuracion(unsigned int id_entrada, unsigned int id_salida)
{
	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();

	m_cantidad_dispositivos_entrada = dispositivos_entrada.size();
	m_cantidad_dispositivos_salida = dispositivos_salida.size();

	this->cambiar_entrada(id_entrada);
	this->cambiar_salida(id_salida);
}

Configuracion::~Configuracion()
{
}

void Configuracion::cambiar_entrada(unsigned int id_entrada)
{
	if(m_cantidad_dispositivos_entrada > 0)
	{
		if(id_entrada < m_cantidad_dispositivos_entrada)
			m_entrada = new MidiCommIn(id_entrada);
		else
			m_entrada = new MidiCommIn(0);
	}
}

void Configuracion::cambiar_salida(unsigned int id_salida)
{
	if(m_cantidad_dispositivos_salida > 0)
	{
		if(id_salida < m_cantidad_dispositivos_salida)
			m_salida = new MidiCommOut(id_salida);
		else
			m_salida = new MidiCommOut(0);
	}
}

MidiCommIn *Configuracion::entrada()
{
	return m_entrada;
}

MidiCommOut *Configuracion::salida()
{
	return m_salida;
}
