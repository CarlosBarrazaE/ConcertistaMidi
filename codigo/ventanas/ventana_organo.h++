#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../recursos/textura_2d.h++"
#include "../elementos/organo.h++"
#include "../pantalla.h++"
#include "../libmidi/Midi.h"
#include "../libmidi/MidiComm.h"
#include "../fps.h++"

class VentanaOrgano : public Ventana
{
private:
	Organo *organo;
	Midi *musica;
	MidiCommIn *midi_entrada;
	MidiCommOut *midi_salida;

	MidiCommDescriptionList dispositivos_entrada;
	MidiCommDescriptionList dispositivos_salida;

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
};
#endif
