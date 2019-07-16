#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../elementos_graficos/barra_progreso.h++"
#include "../elementos_graficos/tablero_notas.h++"
#include "../elementos_graficos/organo.h++"
#include "../control/pista.h++"
#include "../control/tipo_teclados.h++"
#include "../control/configuracion.h++"
#include "../control/datos_musica.h++"
#include "../libmidi/Midi.h++"
#include "../libmidi/MidiComm.h++"
#include <map>

class VentanaOrgano : public Ventana
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Texto *texto_titulo;
	Texto *texto;

	//Componentes
	Barra_Progreso *barra;
	Tablero_Notas *tablero;
	Organo *organo;

	//Controles
	double velocidad_musica;
	bool cambio_velocidad;
	bool pausa;

	//Texto pantalla
	std::string texto_pausa;
	int ancho_titulo;
	int ancho_pausa;

	//Datos
	Configuracion *configuracion;
	Datos_Musica *musica;

public:
	VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaOrgano();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
