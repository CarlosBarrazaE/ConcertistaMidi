#include "fps.h++"

unsigned int Fps::Nanosegundos = 0;
bool Fps::Mostrar_fps = true;
unsigned int Fps::Contador_fps = 0;

Tiempo Fps::Tiempo_actual = Reloj::now();
Tiempo Fps::Tiempo_anterior = Reloj::now();

unsigned int Fps::Tiempo_fotograma()
{
	Fps::Tiempo_actual = Reloj::now();
	Fps::Nanosegundos = std::chrono::duration_cast<std::chrono::nanoseconds>(Fps::Tiempo_actual - Fps::Tiempo_anterior).count();
	Fps::Tiempo_anterior = Fps::Tiempo_actual;
	if(Fps::Contador_fps > 10)
	{
		Fps::Mostrar_fps = true;
		Fps::Contador_fps = 0;
	}
	else
		Fps::Mostrar_fps = false;
	Fps::Contador_fps++;
	return 1000000000.0/Fps::Nanosegundos;//Retorna FPS
}

bool Fps::Actualizar_fps()
{
	return Fps::Mostrar_fps;
}

unsigned int Fps::Obtener_nanosegundos()
{
	return Fps::Nanosegundos;
}
