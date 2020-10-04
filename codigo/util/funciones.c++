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

	bool comparar_float(float valor1, float valor2, float diferencia_minima)
	{
		if(valor1 < valor2 + diferencia_minima && valor1 > valor2 - diferencia_minima)
			return true;
		return false;
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

	std::string convertir_a_utf8(const char *entrada, int largo_entrada, const char *nombre_codificacion)
	{
		UErrorCode  estado = U_ZERO_ERROR;
		UConverter *convertidor = ucnv_open(nombre_codificacion, &estado);

		//Se calcula el tamaño de la nueva cadena
		int32_t largo = ucnv_toUChars(convertidor, NULL, 0, entrada, largo_entrada, &estado);
		//Se omite el error evidente de desbordamiento, no conozco otra forma de calcular el nuevo tamaño
		if(U_FAILURE(estado) && estado != U_BUFFER_OVERFLOW_ERROR)
		{
			Registro::Error("Fallo la conversion: " + std::string(u_errorName(estado)));
			ucnv_close(convertidor);
			return "";
		}

		//Se construye la nueva cadena
		UChar *cadena_salida = new UChar[largo+1];
		estado = U_ZERO_ERROR;
		ucnv_toUChars(convertidor, cadena_salida, largo, entrada, largo_entrada, &estado);
		if(U_FAILURE(estado))
		{
			Registro::Error("Fallo la conversion: " + std::string(u_errorName(estado)));
			ucnv_close(convertidor);
			delete[] cadena_salida;
			return "";
		}

		//Se convierte a un string
		std::string resultado;
		icu::UnicodeString unicode = icu::UnicodeString(cadena_salida, largo);
		unicode.toUTF8String(resultado);

		ucnv_close(convertidor);
		delete[] cadena_salida;

		return resultado;
	}

	bool esta_vacio(const std::string &texto)
	{
		for(unsigned long int x=0; x<texto.length(); x++)
		{
			if(texto[x] != ' ' && texto[x] != '\t' && texto[x] != '\r' && texto[x] != '\n')
				return false;
		}
		return true;
	}
}
