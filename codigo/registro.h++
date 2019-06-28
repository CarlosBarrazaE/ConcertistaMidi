#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <fstream>

#define ARCHIVO_REGISTRO "../registros.txt"
#define IMPRIMIR_PANTALLA 1
#define NIVEL_REGISTRO 3

namespace
{
	enum CodigoEstado
	{
		Error = 0,
		Aviso = 1,
		Dato = 2,
		Depurar = 3
	};
}

class Registro
{
private:
	static void escribir_registro(CodigoEstado estado, std::string texto);
public:
	static void error(std::string texto);
	static void aviso(std::string texto);
	static void nota(std::string texto);
	static void depurar(std::string texto);

	static void error_glfw(int error, const char *descripcion);
	static void mostrar_detalles();
};

#endif
