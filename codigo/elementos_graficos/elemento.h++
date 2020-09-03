#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../recursos/administrador_recursos.h++"
#include "../dispositivos/raton.h++"

class Elemento
{
protected:
	int m_x = 0, m_y = 0;
	int m_ancho = 0, m_alto = 0;
	int m_ax = 0, m_ay = 0;
	bool m_centrado = false;
public:
	Elemento(int x, int y, int ancho, int alto);
	Elemento(int x, int y, int ancho, int alto, bool centrado);
	virtual ~Elemento();

	virtual void actualizar(unsigned int diferencia_tiempo) = 0;
	virtual void dibujar() = 0;
	virtual void evento_raton(Raton *raton) = 0;
	virtual void evento_pantalla(int ancho, int alto) = 0;

	int x();
	int y();
	int ancho();
	int alto();

	void centrado(bool centrado);
	void posicion(int x, int y);
	void x(int x);
	void y(int y);

	void dimension(int ancho, int alto);
	void ancho(int ancho);
	void alto(int alto);

	void ajuste(int x, int y);
};

#endif
