#ifndef TABLERO_NOTAS_H
#define TABLERO_NOTAS_H

#include "elemento.h++"
#include "../recursos/rectangulo.h++"
#include "../util/octava.h++"
#include "../control/pista.h++"
#include "../control/teclado.h++"
#include "../libmidi/Midi.h++"

#include <vector>
#include <array>

class Tablero_Notas : public Elemento
{
private:
	Textura2D *textura_sombra, *textura_nota;
	Rectangulo *rectangulo;
	Texto *texto;

	Teclado *teclado;
	microseconds_t tiempo_actual_midi;
	int ancho_blanca, ancho_negra;
	int ajuste_x;
	int velocidad_caida;
	NotasPistas notas;
	MidiEventMicrosecondList lineas;
	std::array<Color, 52> teclas_activas_blancas;
	std::array<Color, 36> teclas_activas_negras;
	std::vector<int> ultima_nota;//Ultima nota por cada pista

	std::vector<Pista> *pistas;

	void calcular_tamannos();
	void dibujar_lineas_horizontales();
	void dibujar_lineas_verticales();
	void dibujar_notas(int pista_real, int pista);

public:
	Tablero_Notas(int x, int y, int alto, int ancho, Teclado *teclado, Administrador_Recursos *recursos);
	~Tablero_Notas();

	std::array<Color, 52> *o_blancas_presionadas();
	std::array<Color, 36> *o_negras_presionadas();

	void e_tiempo(microseconds_t tiempo);
	void e_notas(NotasPistas notas);
	void e_lineas(MidiEventMicrosecondList lineas);
	void e_pistas(std::vector<Pista> *pistas);
	void e_dimension(int ancho, int alto);
	void c_velocidad_caida(int valor);
	void c_teclado(Teclado *teclado);
	void reiniciar();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
