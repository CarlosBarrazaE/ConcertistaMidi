#ifndef FPS_H
#define FPS_H

class Fps
{
private:
	double tiempo_anterior;
	double fotogramas;
	double fotograma_anterior;
	int contador_fotogramas;
	bool cambio_fps;
public:
	Fps();
	double obtener_fps(double tiempo_actual);
	bool nuevo_fps();
};

#endif
