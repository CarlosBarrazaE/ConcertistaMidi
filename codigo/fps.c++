#include "fps.h++"
#include <iostream>

unsigned int Fps::Nanosegundos = 0;
unsigned int Fps::Nanosegundos_fotogramas = 0;
bool Fps::Mostrar_fps = true;
unsigned int Fps::Contador_fps = 0;

Tiempo Fps::Tiempo_actual = Reloj::now();
Tiempo Fps::Tiempo_anterior = Reloj::now();
Tiempo Fps::Tiempo_anterior_fotogramas = Reloj::now();

unsigned int Fps::Calcular_tiempo()
{
	Fps::Tiempo_actual = Reloj::now();
	Fps::Nanosegundos = std::chrono::duration_cast<std::chrono::nanoseconds>(Fps::Tiempo_actual - Fps::Tiempo_anterior).count();
	Fps::Nanosegundos_fotogramas = std::chrono::duration_cast<std::chrono::nanoseconds>(Fps::Tiempo_actual - Fps::Tiempo_anterior_fotogramas).count();
	Fps::Tiempo_anterior = Fps::Tiempo_actual;

	if(Fps::Nanosegundos_fotogramas >= 250000000)//Mostrar cada 250 milisegundos
	{
		unsigned int fps_total = Fps::Contador_fps + 1;

		Fps::Contador_fps = 0;
		Fps::Tiempo_anterior_fotogramas = Fps::Tiempo_actual;
		Fps::Mostrar_fps = true;

		return 1000000000.0/(static_cast<double>(Fps::Nanosegundos_fotogramas)/static_cast<double>(fps_total));//Retorna FPS
	}
	else
	{
		Fps::Mostrar_fps = false;
		Fps::Contador_fps++;
		return 0;
	}
}

bool Fps::Actualizar_fps()
{
	return Fps::Mostrar_fps;
}

unsigned int Fps::Obtener_nanosegundos()
{
	return Fps::Nanosegundos;
}
