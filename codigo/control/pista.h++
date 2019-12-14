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
	static Color Colores_pista[NUMERO_COLORES_PISTA];
	Pista(std::string instrumento, unsigned int numero_notas, Color color, Modo modo, bool visible, bool sonido);
	~Pista();

	void e_color(Color color);
	void e_modo(Modo modo);
	void e_visible(bool estado);
	void e_sonido(bool estado);

	Color o_color();
	Modo o_modo();
	bool o_visible();
	bool o_sonido();
	std::string o_instrumento();
	unsigned int o_numero_notas();
};

#endif
