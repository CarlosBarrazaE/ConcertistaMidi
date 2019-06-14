#ifndef TEXTURA_2D_H
#define TEXTURA_2D_H

#include <GL/glew.h>

class Textura2D
{
private:
	unsigned int indice_textura;

	unsigned int ancho;
	unsigned int alto;
	unsigned int formato;

	unsigned int envolver_s;
	unsigned int envolver_t;

	unsigned int filtro_minimizar;
	unsigned int filtro_maximizar;

public:
	Textura2D();
	~Textura2D();
	unsigned int o_indice();
	void generar(unsigned int ancho, unsigned int alto, unsigned int bits, unsigned int formato_entrada, unsigned char *datos);
	void activar();

	void e_envolver_horizontal(unsigned int valor);
	void e_envolver_vertical(unsigned int valor);

	void e_filtro_minimizar(unsigned int valor);
	void e_filtro_maximizar(unsigned int valor);

	static unsigned int ultimo_indice_seleccionado;
};

#endif
