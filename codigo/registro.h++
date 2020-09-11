#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <fstream>

#define ARCHIVO_REGISTRO "../registros.txt"
#define IMPRIMIR_TERMINAL 1
#define NIVEL_REGISTRO 3

enum CodigoEstado
{
	EstadoError = 0,
	EstadoAviso = 1,
	EstadoNota = 2,
	EstadoDepurar = 3,
	EstadoNinguno = 4
};

class Registro
{
private:
	static void Escribir_registro(CodigoEstado estado, std::string texto);
public:
	static void Error(std::string texto);
	static void Aviso(std::string texto);
	static void Nota(std::string texto);
	static void Depurar(std::string texto);

	static void Mostrar_detalles();
};

#endif
