#include "archivo.h++"

namespace Archivo
{
	std::string leer_archivo(const char* nombre)
	{
		std::ifstream archivo_texto;
		std::stringstream cadena_texto;
		std::string texto;

		try
		{
			archivo_texto.open(nombre);

			if(!archivo_texto.is_open())
				Registro::Error("Error al abrir el archivo: \"" + std::string(nombre) + "\"");

			cadena_texto << archivo_texto.rdbuf();
			texto = cadena_texto.str();
			archivo_texto.close();
		}
		catch(std::ifstream::failure e)
		{
			Registro::Error("Error con el archivo " + std::string(nombre) + ": " + std::string(e.what()));
		}

		return texto;
	}
}
