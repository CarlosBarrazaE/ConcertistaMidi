#include "octava.h++"

namespace Octava
{
	unsigned int numero_blanca_octava[12] = {1,1,2,2,3,4,4,5,5,6,6,7};//Numero de blancas hasta la posicion en octava
	unsigned int numero_negras_octava[12] = {0,1,1,2,2,2,3,3,4,4,5,5};//Numero de negras hasta la posicion en octava

	bool es_blanca(unsigned int id_nota)
	{
		//Calcula si una nota MIDI es blanca o no
		unsigned int nota = id_nota % 12;//Posicion dentro de la octava
		if(nota == 1 || nota == 3 || nota == 6 || nota == 8 || nota == 10)
			return false;
		return true;
	}

	unsigned int numero_blancas(unsigned int id_nota)
	{
		//Retorna el numero de teclas blancas que hay hasta la nota MIDI incluyendola
		unsigned int octava = id_nota / 12;
		//Hay 7 blancas por octava y se cuenta desde la octava 0
		return octava*7 + numero_blanca_octava[id_nota % 12];
	}

	unsigned int numero_negras(unsigned int id_nota)
	{
		//Retorna el numero de teclas negras que hay hasta la nota MIDI incluyendola
		unsigned int octava = id_nota / 12;
		//Hay 5 negras por octava y se cuenta desde la octava 0
		return octava*5 + numero_negras_octava[id_nota % 12];
	}
}
