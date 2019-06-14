#include "fps.h++"

Fps::Fps()
{
	this->tiempo_anterior = 0;
	this->fotogramas = 0;
	this->fotograma_anterior = 0;
	this->contador_fotogramas = 0;
	this->cambio_fps = false;
}

double Fps::obtener_fps(double tiempo_actual)
{
	double tiempo_transcurrido = tiempo_actual - tiempo_anterior;
	if(tiempo_transcurrido > 0.1)
	{
		tiempo_anterior = tiempo_actual;
		fotogramas = contador_fotogramas / tiempo_transcurrido;
		contador_fotogramas = 0;
		if(fotograma_anterior != fotogramas)
		{
			fotograma_anterior = fotogramas;
			cambio_fps = true;
		}
	}
	else
		cambio_fps = false;
	contador_fotogramas++;
	return fotogramas;
}

bool Fps::nuevo_fps()
{
	return cambio_fps;
}
