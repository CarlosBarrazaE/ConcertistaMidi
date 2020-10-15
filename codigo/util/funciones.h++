#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

#include "../libmidi/Midi.h++"
#include "../libmidi/MidiTypes.h++"
#include "../registro.h++"

namespace Funciones
{
	std::string microsegundo_a_texto(microseconds_t ms, bool mostrar_vacio);
	microseconds_t duracion_midi(std::string ruta_midi);
	bool comparar_float(float valor1, float valor2, float diferencia_minima);
}

#endif
