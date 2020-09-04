#ifndef TABLERO_NOTAS_H
#define TABLERO_NOTAS_H

#include "elemento.h++"
#include "etiqueta.h++"
#include "../recursos/rectangulo.h++"
#include "../util/octava.h++"
#include "../control/pista.h++"
#include "../control/teclado_configuracion.h++"
#include "../libmidi/Midi.h++"

#include <vector>
#include <array>
#include <map>

class Tablero_Notas : public Elemento
{
private:
	Administrador_Recursos *m_recursos;
	Textura2D *m_textura_sombra, *m_textura_nota, *m_textura_nota_resaltada;
	Rectangulo *m_rectangulo;
	Tipografia *m_tipografia;
	std::map<int, Etiqueta*> m_texto_numeros;

	Teclado_Configuracion *m_teclado;
	microseconds_t m_tiempo_actual_midi;
	int m_ancho_blanca, m_ancho_negra;
	int m_ajuste_x;
	int m_duracion_nota;
	NotasPistas m_notas;
	MidiEventMicrosecondList m_lineas;
	std::array<Color, 52> m_teclas_activas_blancas;
	std::array<Color, 36> m_teclas_activas_negras;

	std::array<double, 52> m_tiempo_espera_blancas;
	std::array<double, 36> m_tiempo_espera_negras;

	std::vector<unsigned int> m_ultima_nota;//Ultima nota por cada pista

	std::vector<Pista> *m_pistas;

	void calcular_tamannos();
	void dibujar_lineas_horizontales();
	void dibujar_lineas_verticales();
	void dibujar_notas(int pista);

public:
	Tablero_Notas(int x, int y, int alto, int ancho, Teclado_Configuracion *teclado, Administrador_Recursos *recursos);
	~Tablero_Notas();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(int ancho, int alto) override;

	std::array<Color, 52> *blancas_presionadas();
	std::array<Color, 36> *negras_presionadas();

	void tiempo(microseconds_t tiempo);
	void notas(NotasPistas notas);
	void lineas(MidiEventMicrosecondList lineas);
	void pistas(std::vector<Pista> *pistas);
	void duracion_nota(int valor);
	void modificar_duracion_nota(int valor);
	int duracion_nota();
	void teclado(Teclado_Configuracion *teclado);
	void reiniciar();


};

#endif
