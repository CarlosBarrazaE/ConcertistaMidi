#include "octava.h++"

namespace Octava
{
	bool notas_negras[12] = {false, true, false, true, false, false, true, false, true, false, true, false};
	unsigned int numero_blanca[12] = {1,1,2,2,3,4,4,5,5,6,6,7};
	unsigned int numero_negras[12] = {0,1,1,2,2,2,3,3,4,4,5,5};
	unsigned int negra[12] =  {0,1,0,2,0,0,3,0,4,0,5,0};

	bool es_negra(unsigned int id_nota)
	{
		return notas_negras[id_nota % 12];
	}

	unsigned int prosicion_nota(unsigned int id_nota)
	{
		unsigned int octava = id_nota / 12;//Solo se queda con la parte entera
		unsigned int nota_en_octava = (id_nota % 12);//Numero de nota del 0 al 11

		return octava*7 + numero_blanca[nota_en_octava] - 13;
	}

	unsigned int prosicion_nota_negra(unsigned int id_nota)
	{
		unsigned int octava = id_nota / 12;//Solo se queda con la parte entera
		unsigned int nota_en_octava = (id_nota % 12);//Numero de nota del 0 al 11

		return octava*5 + numero_negras[nota_en_octava] - 10;
	}

	unsigned int numero_negra(unsigned int id_nota)
	{
		unsigned int nota_en_octava = (id_nota % 12);//Numero de nota del 0 al 11
		return negra[nota_en_octava];
	}
}
