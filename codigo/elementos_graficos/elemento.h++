#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "../recursos/administrador_recursos.h++"
#include "../dispositivos/raton.h++"

class Elemento
{
protected:
	float m_x = 0, m_y = 0;
	float m_ancho = 0, m_alto = 0;
	bool m_centrado = false;

	void _posicion(float x, float y);
	void _dimension(float ancho, float alto);
	void _centrado(bool centrado);
public:
	Elemento(float x, float y, float ancho, float alto);
	Elemento(float x, float y, float ancho, float alto, bool centrado);
	virtual ~Elemento();

	virtual void actualizar(unsigned int diferencia_tiempo) = 0;
	virtual void dibujar() = 0;
	virtual void evento_raton(Raton *raton) = 0;

	virtual void posicion(float x, float y);
	virtual void dimension(float ancho, float alto);
	virtual void centrado(bool centrado);

	float x();
	float y();
	float ancho();
	float alto();
};

#endif
