#include "funciones.h++"

namespace Funciones
{
	std::string milisegundos_a_texto(microseconds_t ms)
	{
		int seg  = static_cast<int>(ms / 1000000);
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

	std::vector<std::string> dividir_texto(const std::string &texto, char caracter)
	{
		std::vector<std::string> dividido;
		std::string temporal;
		for(unsigned long int x = 0; x<texto.length(); x++)
		{
			if(texto[x] == caracter)
			{
				if(temporal.length() > 0)
					dividido.push_back(temporal);
				temporal.clear();
			}
			else
			{
				temporal += texto[x];
			}
		}
		if(temporal.length() > 0)
			dividido.push_back(temporal);
		return dividido;
	}

	bool comparar_float(float valor1, float valor2, float diferencia_minima)
	{
		if(valor1 < valor2 + diferencia_minima && valor1 > valor2 - diferencia_minima)
			return true;
		return false;
	}
}
