#ifndef ORGANO_H
#define ORGANO_H

#include "elemento.h++"
#include "../recursos/textura_2d.h++"
#include "../recursos/sombreador.h++"
#include "../recursos/rectangulo.h++"

#define PROPORCION_BLANCA 6.52941
#define PROPORCION_NEGRA 0.657
#define PROPORCION_ANCHO_NEGRA 0.666667

enum Teclado
{
	Teclas88 = 0,	//La 7 52B + 36N
	Teclas76,		//Mi 3 45B + 31N
	Teclas61,		//Do 1 36B + 25N
	Teclas49,		//Do 1 29B + 20N
	Teclas37		//Re 2 22B + 15N
};

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
	int ancho_tecla_blanca;
	int ancho_tecla_negra;
	int alto_tecla_blanca;
	int alto_tecla_negra;
	Teclado tammano_teclado;

	//Metodos
	void dibujar_blancas(int x, int y, int numero_teclas);
	void dibujar_negras(int x, int y, int numero_teclas);

public:
	Organo(int x, int y, int ancho, Teclado tamanno, Administrador_Recursos *recursos);
	~Organo();

	void actualizar_y(int y);
	void actualizar_ancho(int ancho);
	int obtener_alto();

	void actualizar(Raton *raton);
	void dibujar();
};

#endif
