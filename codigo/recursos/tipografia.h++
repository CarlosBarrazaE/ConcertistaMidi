#ifndef TIPOGRAFIA_H
#define TIPOGRAFIA_H

#include <map>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <unicode/unistr.h>

#include "figura.h++"
#include "textura_2d.h++"

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

class Tipografia
{
private:
	FT_Library m_libreria;
	FT_Face m_tipografia;

	std::map<unsigned int, Caracter*> m_caracteres;
	unsigned int m_indice_atlas;
	unsigned int m_ancho_atlas;
	unsigned int m_alto_atlas;

	int m_tamanno_letra;

	void generar_caracteres();
	Caracter *obtener_caracter(unsigned int caracter);
public:
	Tipografia(Formato formato, int tamanno_letra);
	~Tipografia();
    
	int crear_texto(icu::UnicodeString texto, unsigned int *indice_figura, unsigned int *indice_objeto);
	int alto_texto();
	void activar();
};
#endif
