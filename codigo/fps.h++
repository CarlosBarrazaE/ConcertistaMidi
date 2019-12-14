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

	static unsigned int Nanosegundos;

	static bool Mostrar_fps;
	static unsigned int Contador_fps;

public:
	static unsigned int Tiempo_fotograma();
	static bool Actualizar_fps();
	static unsigned int Obtener_nanosegundos();
};

#endif
