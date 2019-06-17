#ifndef DIBUJAR_TEXTO_H
#define DIBUJAR_TEXTO_H

#include <map>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <unicode/unistr.h>

#include "figura.h++"
#include "textura_2d.h++"
#include "sombreador.h++"
#include "color.h++"

#include "../registro.h++"

enum Formato
{
	Normal,
	Negrita,
	Cursiva,
	CursivaNegrita
};

struct Caracter
{
	unsigned int codigo_unicode;
	unsigned int ancho;
	unsigned int alto;
	unsigned int ajuste_izquierda;
	unsigned int ajuste_arriba;
	unsigned int avance_x;
	unsigned int avance_y;
	unsigned int textura_x;//Posicion dentro del atlas
};

class Texto : public Figura
{
private:
	static Color ultimo_color;

	FT_Library libreria;
	FT_Face tipografia;

	std::map<unsigned int, Caracter*> caracteres;
	unsigned int indice_atlas;
	unsigned int ancho_atlas;
	unsigned int alto_atlas;

	unsigned int indice_objeto;
	unsigned int largo_ultimo_texto;

	void generar_caracteres();
	Caracter *obtener_caracter(unsigned int caracter);
	int imprimir_texto(int x, int y, icu::UnicodeString texto, Color color, bool centrado);
	int ancho_texto_unicode(icu::UnicodeString texto);
public:
	Texto(Formato formato, int tamanno_letra, Sombreador *sombreador);
	int dibujar_texto(int x, int y, std::string texto);
	int dibujar_texto(int x, int y, std::string texto, bool centrado);
	int dibujar_texto(int x, int y, std::string texto, Color color);
	int dibujar_texto(int x, int y, std::string texto, Color color, bool centrado);
	int ancho_texto(std::string texto);
};
#endif
