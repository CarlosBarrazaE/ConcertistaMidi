#include "configuracion.h++"

Configuracion::Configuracion()
{
	this->entrada = new MidiCommIn(0);
	this->salida = new MidiCommOut(0);
}

Configuracion::Configuracion(unsigned int id_entrada, unsigned int id_salida)
{
	this->entrada = new MidiCommIn(id_entrada);
	this->salida = new MidiCommOut(id_salida);
}

Configuracion::~Configuracion()
{
}

void Configuracion::cambiar_entrada(unsigned int id_entrada)
{
	this->entrada = new MidiCommIn(id_entrada);
}

void Configuracion::cambiar_salida(unsigned int id_salida)
{
	this->salida = new MidiCommOut(id_salida);
}

MidiCommIn *Configuracion::o_entrada()
{
	return this->entrada;
}

MidiCommOut *Configuracion::o_salida()
{
	return this->salida;
}
