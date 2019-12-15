#ifndef CUADRO_TEXTO_H
#define CUADRO_TEXTO_H

#include <string>
#include "elemento.h++"
#include "../recursos/texto.h++"
#include "../registro.h++"

class Etiqueta : public Elemento
{
private:
    Texto *m_tipografia = NULL;
	Color m_color;
    std::string m_texto;
	bool m_centrado = false;
	int m_largo_texto = 0;
	int m_alto_texto = 0;

public:
	Etiqueta();
	Etiqueta(int x, int y, int ancho, int alto, bool centrado, std::string texto, Texto *tipografia);
	Etiqueta(int x, int y, bool centrado, std::string texto, Texto *tipografia);
    ~Etiqueta();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
	void evento_pantalla(int ancho, int alto);

    void texto(std::string texto);
    void color(Color color);
	void tipografia(Texto *tipografia);
	void tamanno_letra();
	void centrado(bool centrado);

	int largo_texto();
	int alto_texto();
};

#endif
