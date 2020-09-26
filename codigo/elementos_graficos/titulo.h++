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
	float m_posicion_texto;
	float m_alfa;

public:
	Titulo(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Titulo();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(float ancho, float alto) override;

	void datos(Datos_Musica *datos_musica);
};

#endif
