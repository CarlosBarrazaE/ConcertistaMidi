#ifndef BOTON_H
#define BOTON_H

#include "elemento.h++"

//TODO Agregar animacion al cambiar de color
class Boton : public Elemento
{
private:
	Texto *texto;
	Textura2D *textura_boton;
	Rectangulo *rectangulo;

	Color color_boton;
	Color color_boton_normal;
	Color color_boton_sobre;
	Color color_texto;

	int x;
	int y;
	int ancho;
	int alto;
	bool centrado;
	std::string texto_boton;
	int ajuste_texto;

	bool sobre_boton;
	bool boton_pre_activado;
	bool boton_activado;

public:
	Boton(int x, int y, int ancho, int alto, std::string texto, Textura2D *textura, Color color, bool centrado, Administrador_Recursos *recursos);
	~Boton();
	void e_color_texto(Color color);
	void e_letra(Texto *texto);

	void posicion_x(int x);
	void posicion_y(int y);
	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);

	bool esta_activado();
};

#endif
