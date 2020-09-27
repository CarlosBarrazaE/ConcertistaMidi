#ifndef FPS_H
#define FPS_H

#include <chrono>

typedef std::chrono::high_resolution_clock Reloj;
typedef std::chrono::high_resolution_clock::time_point Tiempo;
class Fps
{
private:
	static Tiempo Tiempo_actual;
	static Tiempo Tiempo_anterior;
	static Tiempo Tiempo_anterior_fotogramas;

	static long int Nanosegundos;
	static long int Nanosegundos_fotogramas;

	static bool Mostrar_fps;
	static long int Contador_fps;

public:
	static unsigned int Calcular_tiempo();
	static bool Actualizar_fps();
	static unsigned int Obtener_nanosegundos();
};

#endif
