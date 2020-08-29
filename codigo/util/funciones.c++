#include "funciones.h++"

namespace Funciones
{
	std::string milisegundos_a_texto(microseconds_t ms)
	{
		int seg  = ms / 1000000;
		int horas = seg / 3600;
		int minutos = (seg - (horas * 3600)) / 60;
		int segundos =  (seg - (horas * 3600 + minutos * 60));

		std::string tminutos, tsegundos;
		if(minutos < 10)
			tminutos = "0" + std::to_string(minutos);
		else
			tminutos = std::to_string(minutos);

		if(segundos < 10)
			tsegundos = "0" + std::to_string(segundos);
		else
			tsegundos = std::to_string(segundos);

		return std::to_string(horas) + ":" + tminutos + ":" + tsegundos;
	}
}
