#ifndef PISTA_H
#define PISTA_H

#include "../recursos/color.h++"
#include <string>

#define NUMERO_COLORES_PISTA 9

enum Modo
{
	ManoDerecha,
	ManoIzquierda,
	Fondo,
};

class Pista
{
private:
	Color color_pista;
	Modo modo_pista;
	bool visible;
	bool sonido;
	std::string instrumento;
	unsigned int numero_notas;
public:
	static Color colores_pista[NUMERO_COLORES_PISTA];
	Pista(std::string instrumento, unsigned int numero_notas, Color color, Modo modo, bool visible, bool sonido);
	~Pista();

	Color o_color();
	Modo o_modo();
	bool o_visible();
	bool o_sonido();
	std::string o_instrumento();
	unsigned int o_numero_notas();
};

#endif
