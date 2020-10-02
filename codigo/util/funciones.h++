#ifndef TIEMPO_H
#define TIEMPO_H

#include "../libmidi/MidiTypes.h++"
#include <string>
#include <vector>

namespace Funciones
{
	std::string milisegundos_a_texto(microseconds_t ms);
	std::vector<std::string> dividir_texto(const std::string &texto, char caracter);
	bool comparar_float(float valor1, float valor2, float diferencia_minima);
}

#endif
