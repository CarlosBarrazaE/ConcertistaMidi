#ifndef BARRA_PROGRESO_H
#define BARRA_PROGRESO_H

#include "elemento.h++"
#include "etiqueta.h++"
#include "../util/funciones.h++"
#include "../libmidi/Midi.h++"

class Barra_Progreso : public Elemento
{
private:
	MidiEventMicrosecondList m_lineas;
	microseconds_t m_tiempo_total;
	microseconds_t m_tiempo_actual;
	microseconds_t m_tiempo_nuevo;
	int m_x_anterior;
	int m_progreso;
	bool m_sobre_barra;

	Textura2D *m_frente;
	Etiqueta m_texto_inicial, m_texto_final;
	Rectangulo *m_rectangulo;

	Color m_color_fondo;
	Color m_color_progreso;
public:
	Barra_Progreso(int x, int y, int ancho, int alto, microseconds_t tiempo_total, MidiEventMicrosecondList lineas, Administrador_Recursos *recursos);
	~Barra_Progreso();

	void tiempo(microseconds_t tiempo_actual);
	microseconds_t o_tiempo_seleccionado();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;
	void evento_pantalla(int ancho, int alto) override;
};

#endif
