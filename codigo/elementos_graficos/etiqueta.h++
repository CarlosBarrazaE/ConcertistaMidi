#ifndef ETIQUETA_H
#define ETIQUETA_H

#include <string>
#include <unicode/unistr.h>
#include "elemento.h++"
#include "../recursos/tipografia.h++"
#include "../registro.h++"

class Etiqueta : public Elemento
{
private:
	static Color Ultimo_color;
	Tipografia *m_tipografia = NULL;
	Color m_color;
	icu::UnicodeString m_texto;
	std::string m_texto_actual;
	bool m_centrado = false;
	int m_ancho_texto = 0;
	int m_alto_texto = 0;

	Sombreador *m_sombreador;
	unsigned int m_indice_figura = 0;
	unsigned int m_indice_objeto = 0;

	void actualizar_texto();
	void limpiar();

public:
	Etiqueta(Administrador_Recursos *recursos);
	Etiqueta(int x, int y, bool centrado, std::string texto, ModeloLetra tipografia, Administrador_Recursos *recursos);
	Etiqueta(int x, int y, bool centrado, std::string texto, Tipografia *tipografia, Administrador_Recursos *recursos);
	Etiqueta(int x, int y, int ancho, int alto, bool centrado, std::string texto, ModeloLetra tipografia, Administrador_Recursos *recursos);
	~Etiqueta();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;
	void evento_pantalla(int ancho, int alto) override;

	void texto(std::string texto);
	void color(Color color);
	void tipografia(Tipografia *tipografia);
	void centrado(bool centrado);

	int largo_texto();
	int alto_texto();
	std::string texto();
};

#endif
