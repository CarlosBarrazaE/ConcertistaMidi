#ifndef TIEMPO_H
#define TIEMPO_H

#include "../libmidi/MidiTypes.h++"
#include "../registro.h++"
#include <string>
#include <vector>

//Convertir a utf8
#include <unicode/unistr.h>
#include <unicode/ucnv.h>

namespace Funciones
{
	std::string milisegundos_a_texto(microseconds_t ms);
	bool comparar_float(float valor1, float valor2, float diferencia_minima);

	std::vector<std::string> dividir_texto(const std::string &texto, char caracter);
	std::string convertir_a_utf8(const char *entrada, int largo, const char *nombre_codificacion);
	bool esta_vacio(const std::string &texto);
	std::string remplazar_caracter(const std::string &texto, const char caracter_origen, const char caracter_destino);
}

#endif
