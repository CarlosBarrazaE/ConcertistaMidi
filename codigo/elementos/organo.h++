#ifndef ORGANO_H
#define ORGANO_H

#include "elemento.h++"
#include "../recursos/textura_2d.h++"
#include "../recursos/sombreador.h++"
#include "../recursos/rectangulo.h++"
#include "tipo_teclado.h++"

class Organo : public Elemento
{
private:
	int n_negras[5] = {36, 31, 25, 20, 15};
	int n_blancas[5] = {52, 45, 36, 29, 22};
	int blanca_inicio[5] = {1, 1, 0, 0, 0};
	int negra_inicio[5] = {4, 2, 0, 0, 2};

	Sombreador *sombreador;
	Sombreador *sombreador2;
	//Textura2D *textura_boton;
	//Texto *texto;
	Rectangulo *fondo;
	Rectangulo *teclas;

	Textura2D *tecla_blanca;
	Textura2D *tecla_negra;
	Textura2D *borde_negro;
	Textura2D *borde_rojo;

	int x, y, ancho, alto;
	int ancho_real, ajuste_x;
	int ancho_tecla_blanca, ancho_tecla_negra;
	int alto_tecla_blanca, alto_tecla_negra;
	Teclado tammano_teclado;

	//Metodos
	void dibujar_blancas(int x, int y, int numero_teclas);
	void dibujar_negras(int x, int y, int numero_teclas);
	void calcular_tamannos();

public:
	Organo(int x, int y, int ancho, Teclado tamanno, Administrador_Recursos *recursos);
	~Organo();

	void e_y(int valor);
	void e_ancho(int valor);

	int o_alto();
	int o_ancho_real();
	int o_ajuste_x();
	int o_ancho_blancas();
	int o_ancho_negras();

	void actualizar(Raton *raton);
	void dibujar();
};

#endif
