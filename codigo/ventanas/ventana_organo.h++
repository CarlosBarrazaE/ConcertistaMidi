#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../recursos/textura_2d.h++"
#include "../elementos/tablero_notas.h++"
#include "../elementos/organo.h++"
#include "../pantalla.h++"
#include "../libmidi/Midi.h"
#include "../libmidi/MidiComm.h"
#include "../fps.h++"
#include "../pista.h++"
#include <map>

class VentanaOrgano : public Ventana
{
private:
	Tablero_Notas *tablero;
	Organo *organo;
	Texto *texto;

	Midi *musica;
	MidiCommIn *midi_entrada;
	MidiCommOut *midi_salida;

	std::map<int, Pista*> pistas;
	double velocidad_musica;

	/*
unsigned int id;
std::string name;
int client;
int port;
	 */
public:
	VentanaOrgano(Administrador_Recursos *recursos);
	~VentanaOrgano();

	void actualizar(Raton *raton);
	void dibujar();
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
