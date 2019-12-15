#ifndef TITULO_H
#define TITULO_H

#include "elemento.h++"
#include "etiqueta.h++"
#include "../control/datos_musica.h++"

class Titulo : public Elemento
{
private:
	Rectangulo *m_rectangulo;
	Textura2D *m_fondo;
	Datos_Musica *m_datos;

	Etiqueta m_titulo, m_autor;

	unsigned short int m_estado;
	unsigned int m_tiempo = 0;
	int m_posicion_texto;
	float m_alfa;

public:
	Titulo(int x, int y, int ancho, int alto, Administrador_Recursos *recursos);
	~Titulo();

	void datos(Datos_Musica *datos_musica);
	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
	void evento_pantalla(int ancho, int alto);
};

#endif
