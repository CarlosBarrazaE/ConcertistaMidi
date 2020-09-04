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

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(int ancho, int alto) override;

	void datos(Datos_Musica *datos_musica);
};

#endif
