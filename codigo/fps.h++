#ifndef FPS_H
#define FPS_H

#include <chrono>

typedef std::chrono::high_resolution_clock Reloj;
typedef std::chrono::high_resolution_clock::time_point Tiempo;
class Fps
{
private:
	static Tiempo tiempo_actual;
	static Tiempo tiempo_anterior;

	static unsigned int nanosegundos;

	static bool mostrar_fps;
	static unsigned int contador_fps;

public:
	static unsigned int tiempo_fotograma();
	static bool actualizar_fps();
	static unsigned int obtener_nanosegundos();
};

#endif
