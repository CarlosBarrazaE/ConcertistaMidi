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
#include <vector>

class Organo : public Elemento
{
private:
	Rectangulo *rectangulo;

	Textura2D *tecla_blanca;
	Textura2D *tecla_negra;
	Textura2D *tecla_blanca_presionada;
	Textura2D *tecla_blanca_presionada_doble;
	Textura2D *tecla_negra_presionada;
	Textura2D *borde_negro;
	Textura2D *borde_rojo;

	Teclado *teclado;
	int x, y, ancho, alto;
	int ancho_real, ajuste_x;
	int ancho_tecla_blanca, ancho_tecla_negra;
	int alto_tecla_blanca, alto_tecla_negra;

	std::array<Color, 52> *teclas_activas_blancas;
	std::array<Color, 36> *teclas_activas_negras;

	//Metodos
	void dibujar_blancas(int x, int y, int numero_teclas);
	void dibujar_negras(int x, int y, int numero_teclas);
	void calcular_tamannos();

public:
	Organo(int x, int y, int ancho, Teclado *teclado, Administrador_Recursos *recursos);
	~Organo();

	int o_alto();

	void e_y(int valor);
	void e_ancho(int valor);
	void c_teclado(Teclado *teclado);

	void e_blancas_presionadas(std::array<Color, 52> *teclas_blancas);
	void e_negras_presionadas(std::array<Color, 36> *teclas_negras);

	void actualizar(Raton *raton);
	void dibujar();
};

#endif
