#ifndef ENTRADA_TEXTO_H
#define ENTRADA_TEXTO_H

#include <string>
#include <unicode/unistr.h>
#include "elemento.h++"
#include "etiqueta.h++"

class Entrada_Texto : public Elemento
{
private:
	Rectangulo *m_rectangulo;

	Etiqueta m_texto_mostrado;

	icu::UnicodeString m_texto;
	std::string m_ptexto;

	//Control de animacion
	bool m_cursor;
	float m_tiempo_cursor;
	float m_posicion_cursor;

public:
	Entrada_Texto(float x, float y, float ancho, float alto, std::string texto, Administrador_Recursos *recursos);
	~Entrada_Texto();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void evento_texto(std::string texto);
};

#endif
