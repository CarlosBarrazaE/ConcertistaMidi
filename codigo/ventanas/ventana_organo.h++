#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../recursos/textura_2d.h++"
#include "../elementos_graficos/barra_progreso.h++"
#include "../elementos_graficos/tablero_notas.h++"
#include "../elementos_graficos/organo.h++"
#include "../elementos/pista.h++"
#include "../elementos/tipo_teclados.h++"
#include "../fps.h++"
#include "../libmidi/Midi.h"
#include "../libmidi/MidiComm.h"
#include <map>

class VentanaOrgano : public Ventana
{
private:
	Barra_Progreso *barra;
	Tablero_Notas *tablero;
	Organo *organo;
	Texto *texto;

	std::map<int, Pista*> pistas;
	double velocidad_musica;

	Midi *musica;
	MidiCommIn *midi_entrada;
	MidiCommOut *midi_salida;

public:
	VentanaOrgano(Administrador_Recursos *recursos);
	~VentanaOrgano();

	void actualizar(Raton *raton);
	void dibujar();
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
