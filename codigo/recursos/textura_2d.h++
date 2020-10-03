#ifndef TEXTURA_2D_H
#define TEXTURA_2D_H

#include <GL/glew.h>

class Textura2D
{
private:
	unsigned int m_indice_textura;

	int m_ancho;
	int m_alto;
	unsigned int m_formato;

	int m_envolver_s;
	int m_envolver_t;

	int m_filtro_minimizar;
	int m_filtro_maximizar;

public:
	Textura2D();
	~Textura2D();
	void generar(int ancho, int alto, unsigned int bits, unsigned char *datos);
	void activar();

	void envolver_horizontal(int valor);
	void envolver_vertical(int valor);
	void envolver(int s, int t);

	void filtro_minimizar(int valor);
	void filtro_maximizar(int valor);

	static unsigned int Ultimo_indice_seleccionado;
};

#endif
