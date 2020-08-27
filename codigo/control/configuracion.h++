#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "../libmidi/MidiComm.h++"

#include "base_de_datos.h++"
#include "../util/usuario.h++"

class Configuracion
{
private:
	Base_de_Datos m_datos;

	MidiCommIn *m_entrada;
	MidiCommOut *m_salida;

public:
	Configuracion();
	~Configuracion();

	std::string leer(std::string atributo);
	bool escribir(std::string atributo, std::string valor);

	void dispositivo_entrada(unsigned int id_entrada);
	void dispositivo_salida(unsigned int id_salida);

	MidiCommIn *dispositivo_entrada();
	MidiCommOut *dispositivo_salida();
};

#endif
