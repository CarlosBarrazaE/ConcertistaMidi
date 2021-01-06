#include "octava.h++"

namespace Octava
{
	unsigned int numero_blanca_octava[12] = {1,1,2,2,3,4,4,5,5,6,6,7};//Numero de blancas hasta la posicion en octava
	unsigned int numero_negras_octava[12] = {0,1,1,2,2,2,3,3,4,4,5,5};//Numero de negras hasta la posicion en octava
	//Para agregar la cantidad de negras que faltan segun la posicion de la blanca en la octava
	unsigned int suma_id_nota[7] = {0, 2, 4, 5, 7, 9, 11};

	bool es_blanca(unsigned int id_nota)
	{
		//Calcula si una nota MIDI es blanca o no
		unsigned int nota = id_nota % 12;//Posicion dentro de la octava
		if(nota == 1 || nota == 3 || nota == 6 || nota == 8 || nota == 10)
			return false;
		return true;
	}

	unsigned int blancas_desde_inicio(unsigned id_nota)
	{
		//Retorna el numero de blancas desde el inicio incluyendo a id_nota si corresponde
		if(id_nota > 128)
			id_nota = 0;

		unsigned int octava = id_nota / 12;
		//Hay 7 blancas por octava y se cuenta desde la octava 0
		return octava*7 + numero_blanca_octava[id_nota % 12];
	}

	unsigned int negras_desde_inicio(unsigned id_nota)
	{
		//Retorna el numero de negras desde el inicio incluyendo a id_nota si corresponde
		if(id_nota > 128)
			id_nota = 0;
		unsigned int octava = id_nota / 12;
		//Hay 5 negras por octava y se cuenta desde la octava 0
		return octava*5 + numero_negras_octava[id_nota % 12];
	}

	unsigned int numero_blancas(unsigned int inicio, unsigned int largo)
	{
		//Retorna el numero de blancas empezando a contar desde inicio
		unsigned int blancas_omitidas = 0;
		if(inicio > 0)
			blancas_omitidas = blancas_desde_inicio(inicio-1);
		unsigned int blancas_totales = blancas_desde_inicio(inicio+largo-1);
		return blancas_totales - blancas_omitidas;
	}

	unsigned int numero_negras(unsigned int inicio, unsigned int largo)
	{
		//Retorna el numero de negras empezando a contar desde inicio
		unsigned int negras_omitidas = 0;
		if(inicio > 0)
			negras_omitidas = negras_desde_inicio(inicio-1);
		unsigned int negras_totales = negras_desde_inicio(inicio+largo-1);
		return negras_totales - negras_omitidas;
	}

	unsigned int nota_id_desde_blanca(unsigned int blanca_actual)
	{
		//Retorna el id de la nota (0-127) desde el numero de blancas hasta la actual
		unsigned int octava_actual = blanca_actual / 7;
		return octava_actual*12 + suma_id_nota[blanca_actual % 7];
	}
}
