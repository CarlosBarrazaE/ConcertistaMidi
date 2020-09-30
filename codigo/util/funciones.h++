#ifndef TIEMPO_H
#define TIEMPO_H

#include "../libmidi/MidiTypes.h++"
#include <string>
#include <vector>

namespace Funciones
{
	std::string milisegundos_a_texto(microseconds_t ms);
	std::vector<std::string> dividir_texto(const std::string &texto, char caracter);
}

#endif
