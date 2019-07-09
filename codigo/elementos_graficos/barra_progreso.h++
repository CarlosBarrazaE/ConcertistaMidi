#ifndef BARRA_PROGRESO_H
#define BARRA_PROGRESO_H

#include "elemento.h++"
#include "../elementos/funciones.h++"
#include "../libmidi/Midi.h++"

class Barra_Progreso : Elemento
{
private:
	MidiEventMicrosecondList lineas;
	microseconds_t tiempo_total;
	microseconds_t tiempo_actual;
	microseconds_t tiempo_nuevo;
	int x, y, ancho, alto;
	int x_anterior;
	int progreso;
	bool sobre_barra;

	Textura2D *t_frente;
	Texto *texto;
	Rectangulo *rectangulo;

	std::string duracion_total;
	int largo_texto;

	Color *color_fondo;
	Color *color_progreso;
public:
	Barra_Progreso(int x, int y, int ancho, int alto, microseconds_t tiempo_total, MidiEventMicrosecondList lineas, Administrador_Recursos *recursos);
	~Barra_Progreso();

	void e_tiempo(microseconds_t tiempo_actual);
	void e_ancho(int ancho);

	int o_alto();
	int o_ancho();
	microseconds_t o_tiempo_seleccionado();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
