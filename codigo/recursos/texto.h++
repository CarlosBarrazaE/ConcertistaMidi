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
	int ancho;
	int alto;
	int ajuste_izquierda;
	int ajuste_arriba;
	unsigned int avance_x;
	unsigned int avance_y;
	unsigned int textura_x;//Posicion dentro del atlas
};

class Texto : public Figura
{
private:
	static Color Ultimo_color;

	FT_Library m_libreria;
	FT_Face m_tipografia;

	std::map<unsigned int, Caracter*> m_caracteres;
	unsigned int m_indice_atlas;
	unsigned int m_ancho_atlas;
	unsigned int m_alto_atlas;

	unsigned int m_indice_objeto;
	unsigned int m_largo_ultimo_texto;
	int m_tamanno_letra;

	void generar_caracteres();
	Caracter *obtener_caracter(unsigned int caracter);
	int imprimir_texto(int x, int y, icu::UnicodeString texto, Color color);
	int ancho_texto_unicode(icu::UnicodeString texto);
public:
	Texto(Formato formato, int tamanno_letra, Sombreador *sombreador);
	~Texto();
	int imprimir(int x, int y, std::string texto);
	int imprimir(int x, int y, std::string texto, Color color);
	int ancho_texto(std::string texto);
	int alto_texto();
};
#endif
