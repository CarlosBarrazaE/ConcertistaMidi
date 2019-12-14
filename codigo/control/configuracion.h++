#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "../libmidi/MidiComm.h++"

class Configuracion
{
private:
	MidiCommIn *m_entrada;
	MidiCommOut *m_salida;

public:
	Configuracion();
	Configuracion(unsigned int id_entrada, unsigned int id_salida);
	~Configuracion();

	void cambiar_entrada(unsigned int id_entrada);
	void cambiar_salida(unsigned int id_salida);
	MidiCommIn *o_entrada();
	MidiCommOut *o_salida();
};

#endif
