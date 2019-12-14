#ifndef TABLERO_NOTAS_H
#define TABLERO_NOTAS_H

#include "elemento.h++"
#include "../recursos/rectangulo.h++"
#include "../util/octava.h++"
#include "../control/pista.h++"
#include "../control/teclado_configuracion.h++"
#include "../libmidi/Midi.h++"

#include <vector>
#include <array>

class Tablero_Notas : public Elemento
{
private:
	Textura2D *m_textura_sombra, *m_textura_nota;
	Rectangulo *m_rectangulo;
	Texto *m_texto;

	Teclado_Configuracion *m_teclado;
	microseconds_t m_tiempo_actual_midi;
	int m_ancho_blanca, m_ancho_negra;
	int m_ajuste_x;
	int m_velocidad_caida;
	NotasPistas m_notas;
	MidiEventMicrosecondList m_lineas;
	std::array<Color, 52> m_teclas_activas_blancas;
	std::array<Color, 36> m_teclas_activas_negras;

	std::array<double, 52> m_tiempo_espera_blancas;
	std::array<double, 36> m_tiempo_espera_negras;

	std::vector<int> m_ultima_nota;//Ultima nota por cada pista

	std::vector<Pista> *m_pistas;

	void calcular_tamannos();
	void dibujar_lineas_horizontales();
	void dibujar_lineas_verticales();
	void dibujar_notas(int pista);

public:
	Tablero_Notas(int x, int y, int alto, int ancho, Teclado_Configuracion *teclado, Administrador_Recursos *recursos);
	~Tablero_Notas();

	std::array<Color, 52> *o_blancas_presionadas();
	std::array<Color, 36> *o_negras_presionadas();

	void e_tiempo(microseconds_t tiempo);
	void e_notas(NotasPistas notas);
	void e_lineas(MidiEventMicrosecondList lineas);
	void e_pistas(std::vector<Pista> *pistas);
	void e_dimension(int ancho, int alto);
	void c_velocidad_caida(int valor);
	void c_teclado(Teclado_Configuracion *teclado);
	void reiniciar();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
	void evento_pantalla(int ancho, int alto);
};

#endif
