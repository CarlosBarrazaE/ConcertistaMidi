#include "fps.h++"

int Fps::nanosegundos = 0;
bool Fps::mostrar_fps = true;
int Fps::contador_fps = 0;

Tiempo Fps::tiempo_actual = Reloj::now();
Tiempo Fps::tiempo_anterior = Reloj::now();

int Fps::tiempo_fotograma()
{
	Fps::tiempo_actual = Reloj::now();
	Fps::nanosegundos = std::chrono::duration_cast<std::chrono::nanoseconds>(Fps::tiempo_actual - Fps::tiempo_anterior).count();
	Fps::tiempo_anterior = tiempo_actual;
	if(Fps::contador_fps > 10)
	{
		Fps::mostrar_fps = true;
		Fps::contador_fps = 0;
	}
	else
		Fps::mostrar_fps = false;
	Fps::contador_fps++;
	return 1000000000.0/Fps::nanosegundos;//Retorna FPS
}

bool Fps::actualizar_fps()
{
	return Fps::mostrar_fps;
}

int Fps::obtener_nanosegundos()
{
	return Fps::nanosegundos;
}
