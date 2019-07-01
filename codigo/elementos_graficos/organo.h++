#ifndef ORGANO_H
#define ORGANO_H

#include "elemento.h++"
#include "../recursos/rectangulo.h++"
#include "../elementos/octava.h++"
#include "../elementos/pista.h++"
#include "../elementos/nota.h++"
#include "../elementos/teclado.h++"
#include "../libmidi/Midi.h"

#include <map>

class Organo : public Elemento
{
private:
	Sombreador *sombreador;
	Sombreador *sombreador2;
	//Textura2D *textura_boton;
	//Texto *texto;
	Rectangulo *fondo;
	Rectangulo *teclas;

	Textura2D *tecla_blanca;
	Textura2D *tecla_negra;
	Textura2D *tecla_negra_presionada;
	Textura2D *borde_negro;
	Textura2D *borde_rojo;

	Teclado *teclado;
	int x, y, ancho, alto;
	microseconds_t tiempo_actual_midi;
	int ancho_real, ajuste_x;
	int ancho_tecla_blanca, ancho_tecla_negra;
	int alto_tecla_blanca, alto_tecla_negra;
	TranslatedNoteSet notas;
	std::map<int, Pista*> *pistas;

	std::map<int, Nota> notas_activas_blancas;
	std::map<int, Nota> notas_activas_negras;

	//Metodos
	void dibujar_blancas(int x, int y, int numero_teclas);
	void dibujar_negras(int x, int y, int numero_teclas);
	void calcular_tamannos();

public:
	Organo(int x, int y, int ancho, Teclado *teclado, Administrador_Recursos *recursos);
	~Organo();

	void e_y(int valor);
	void e_ancho(int valor);
	void e_tiempo(microseconds_t tiempo);
	void e_notas(TranslatedNoteSet notas);
	void e_pistas(std::map<int, Pista*> *pistas);
	void c_teclado(Teclado *teclado);
	void limpiar_teclado();

	int o_alto();

	void actualizar(Raton *raton);
	void dibujar();
};

#endif
