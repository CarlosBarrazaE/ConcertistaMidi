#ifndef TEXTURA_2D_H
#define TEXTURA_2D_H

#include <GL/glew.h>

class Textura2D
{
private:
	unsigned int m_indice_textura;

	unsigned int m_ancho;
	unsigned int m_alto;
	unsigned int m_formato;

	unsigned int m_envolver_s;
	unsigned int m_envolver_t;

	unsigned int m_filtro_minimizar;
	unsigned int m_filtro_maximizar;

public:
	Textura2D();
	~Textura2D();
	unsigned int o_indice();
	void generar(unsigned int ancho, unsigned int alto, unsigned int bits, unsigned char *datos);
	void activar();

	void envolver_horizontal(unsigned int valor);
	void envolver_vertical(unsigned int valor);
	void envolver(unsigned int s, unsigned int t);

	void filtro_minimizar(unsigned int valor);
	void filtro_maximizar(unsigned int valor);

	static unsigned int Ultimo_indice_seleccionado;
};

#endif
