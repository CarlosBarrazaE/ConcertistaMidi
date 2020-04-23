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
	Color m_color_pista;
	Modo m_modo_pista;
	bool m_visible;
	bool m_sonido;
	std::string m_instrumento;
	unsigned int m_numero_notas;
public:
	static Color Colores_pista[NUMERO_COLORES_PISTA+1];
	Pista(std::string instrumento, unsigned int numero_notas, Color color, Modo modo, bool visible, bool sonido);
	~Pista();

	void color(Color color);
	void modo(Modo modo);
	void visible(bool estado);
	void sonido(bool estado);

	Color color();
	Modo modo();
	bool visible();
	bool sonido();
	std::string instrumento();
	unsigned int numero_notas();
};

#endif
