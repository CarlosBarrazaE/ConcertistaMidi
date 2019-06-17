#include "texto.h++"

Color Texto::ultimo_color;

Texto::Texto(Formato formato, int tamanno_letra, Sombreador *sombreador) : Figura(sombreador)
{
	if(FT_Init_FreeType(&this->libreria))
		Registro::error("La libreria Freetype fallo al iniciar.");

	std::string ruta_tipografia = "";
	if(formato == Normal)
		ruta_tipografia = "../tipografias/NotoSans-Regular.ttf";
	else if(formato == Negrita)
		ruta_tipografia = "../tipografias/NotoSans-Black.ttf";
	else if(formato == Cursiva)
		ruta_tipografia = "../tipografias/NotoSans-Italic.ttf";
	else if(formato == CursivaNegrita)
		ruta_tipografia = "../tipografias/NotoSans-BlackItalic.ttf";

	if(FT_New_Face(this->libreria, ruta_tipografia.c_str(), 0, &this->tipografia))
		Registro::error("Freetype fallo al cargar la tipografia del archivo: " + ruta_tipografia);

	if(tamanno_letra > 50)
		tamanno_letra = 50;
	else if(tamanno_letra < 5)
		tamanno_letra = 5;

	FT_Set_Char_Size(this->tipografia, 0, tamanno_letra*64, 91.79, 91.79);

	glGenVertexArrays(1, &this->indice_figura);
	glBindVertexArray(this->indice_figura);
	Figura::ultimo_indice_seleccionado = this->indice_figura;

	glGenBuffers(1, &this->indice_objeto);
	glBindBuffer(GL_ARRAY_BUFFER, this->indice_objeto);
	glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	generar_caracteres();

	largo_ultimo_texto = 0;
}

void Texto::generar_caracteres()
{
	icu::UnicodeString idioma_espannol = "0123456789 ⁰¹²³⁴⁵⁶⁷⁸⁹ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyzÁÉÍÓÚáéíóúÄËÏÖÜäëïöü,.-;:'·#$€%&@\"\\()[]{}+-*/=¿?¡!<>ºªḉḈçÇ^";

	int contador = 0;
	this->ancho_atlas = 0;
	this->alto_atlas = 0;
	bool error = false;
	FT_UInt letra_actual;
	for(int n=0; n<idioma_espannol.length(); n++)
	{
		letra_actual = FT_Get_Char_Index(this->tipografia, idioma_espannol[n]);
		if(letra_actual == 0)
		{
			Registro::aviso("Caracter unicode desconocido \"" + std::to_string(idioma_espannol[n]) + "\" se requiere otra tipografia.");
			continue;
		}

		error = FT_Load_Glyph(this->tipografia, letra_actual, FT_LOAD_RENDER);
		if(error)
		{
			Registro::error("Error al cargar el caracter: " + std::to_string(idioma_espannol[n]));
			continue;
		}

		FT_GlyphSlot letra = this->tipografia->glyph;

		this->ancho_atlas += letra->bitmap.width;
		if(letra->bitmap.rows > this->alto_atlas)
			this->alto_atlas = letra->bitmap.rows;
		contador++;
	}


	this->indice_atlas = 0;
	glGenTextures(1, &this->indice_atlas);
	glBindTexture(GL_TEXTURE_2D, this->indice_atlas);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	Textura2D::ultimo_indice_seleccionado = this->indice_atlas;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->ancho_atlas, this->alto_atlas, 0, GL_RED,GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	letra_actual = 0;
	int posicion_textura = 0;
	for(int n=0; n<idioma_espannol.length(); n++)
	{
		letra_actual = FT_Get_Char_Index(this->tipografia, idioma_espannol[n]);
		if(letra_actual == 0)
		{
			Registro::aviso("Caracter unicode desconocido \"" + std::to_string(idioma_espannol[n]) + "\" se requiere otra tipografia.");
			continue;
		}

		error = FT_Load_Glyph(this->tipografia, letra_actual, FT_LOAD_RENDER);
		if(error)
		{
			Registro::error("Error al cargar el caracter: " + std::to_string(idioma_espannol[n]));
			continue;
		}

		FT_GlyphSlot letra = this->tipografia->glyph;

		Caracter *letra_nueva = new Caracter();
		letra_nueva->codigo_unicode = letra_actual;
		letra_nueva->ancho = letra->bitmap.width;
		letra_nueva->alto = letra->bitmap.rows;
		letra_nueva->ajuste_izquierda = letra->bitmap_left;
		letra_nueva->ajuste_arriba = letra->bitmap_top;
		letra_nueva->avance_x = letra->advance.x;
		letra_nueva->avance_y = letra->advance.y;
		letra_nueva->textura_x = posicion_textura;
		caracteres[idioma_espannol[n]] = letra_nueva;

		glTexSubImage2D(GL_TEXTURE_2D, 0, posicion_textura, 0, letra->bitmap.width, letra->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, letra->bitmap.buffer);
		posicion_textura += letra->bitmap.width;
	}
}

Caracter *Texto::obtener_caracter(unsigned int caracter)
{
	return caracteres[caracter];
}

int Texto::imprimir_texto(int x, int y, icu::UnicodeString texto, Color color, bool centrado)
{
	if(centrado)
	{
		int ancho = ancho_texto_unicode(texto);
		x = x - ancho / 2.0;
	}

	int x_inicial = x;

	sombreador->activar();
	if(Texto::ultimo_color != color)
	{
		sombreador->e_vector3f("color_texto", color.o_rojo(), color.o_verde(), color.o_azul());
		Texto::ultimo_color = color;
	}

	if(Figura::ultimo_indice_seleccionado != this->indice_figura)
	{
		glBindVertexArray(this->indice_figura);
		Figura::ultimo_indice_seleccionado = this->indice_figura;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->indice_objeto);

	if(largo_ultimo_texto < texto.length())
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * texto.length(), NULL, GL_DYNAMIC_DRAW);
		largo_ultimo_texto = texto.length();
	}

	if(Textura2D::ultimo_indice_seleccionado != this->indice_atlas)
	{
		glBindTexture(GL_TEXTURE_2D, this->indice_atlas);
		Textura2D::ultimo_indice_seleccionado = this->indice_atlas;
	}

	Caracter *letra;
	unsigned int letra_anterior = 0;
	float vertices[6*texto.length()][4];
	int posicion_arreglo = 0;
	for(int n=0; n<texto.length(); n++)
	{
		letra = obtener_caracter((unsigned int)texto[n]);
		if(!letra)
			continue;

		//Se calcula el Interletraje
		FT_Bool interletraje = FT_HAS_KERNING(this->tipografia);
		if(interletraje && letra_anterior && letra->codigo_unicode)
		{
			FT_Vector delta;
			FT_Get_Kerning(this->tipografia, letra_anterior, letra->codigo_unicode, FT_KERNING_DEFAULT, &delta);
			x += delta.x >> 6;
		}

		float xpos = x + letra->ajuste_izquierda;
		float ypos = y - letra->ajuste_arriba;

		float an = letra->ancho;
		float al = letra->alto;
		vertices[posicion_arreglo][0] = xpos + an;
		vertices[posicion_arreglo][1] = ypos;
		vertices[posicion_arreglo][2] = (letra->textura_x + an) / (float)this->ancho_atlas;//mi valor / total
		vertices[posicion_arreglo][3] = 0.0;
		posicion_arreglo++;

		vertices[posicion_arreglo][0] = xpos;
		vertices[posicion_arreglo][1] = ypos;
		vertices[posicion_arreglo][2] = letra->textura_x / (float)this->ancho_atlas;
		vertices[posicion_arreglo][3] = 0.0;
		posicion_arreglo++;

		vertices[posicion_arreglo][0] = xpos + an;
		vertices[posicion_arreglo][1] = ypos + al;
		vertices[posicion_arreglo][2] = (letra->textura_x + an) / (float)this->ancho_atlas;
		vertices[posicion_arreglo][3] = al / (float)this->alto_atlas;
		posicion_arreglo++;

		vertices[posicion_arreglo][0] = xpos;
		vertices[posicion_arreglo][1] = ypos + al;
		vertices[posicion_arreglo][2] = letra->textura_x / (float)this->ancho_atlas;
		vertices[posicion_arreglo][3] = al / (float)this->alto_atlas;
		posicion_arreglo++;

		vertices[posicion_arreglo][0] = xpos + an;
		vertices[posicion_arreglo][1] = ypos + al;
		vertices[posicion_arreglo][2] = (letra->textura_x + an) / (float)this->ancho_atlas;
		vertices[posicion_arreglo][3] = al / (float)this->alto_atlas;
		posicion_arreglo++;

		vertices[posicion_arreglo][0] = xpos;
		vertices[posicion_arreglo][1] = ypos;
		vertices[posicion_arreglo][2] = letra->textura_x / (float)this->ancho_atlas;
		vertices[posicion_arreglo][3] = 0.0;
		posicion_arreglo++;
/*
		float vertices[6][4] = {
			{xpos + an,	ypos,		1.0,	0.0},
			{xpos + an,	ypos + al,	1.0,	1.0},
			{xpos,		ypos,		0.0,	0.0},

			{xpos,		ypos + al,	0.0,	1.0},
			{xpos + an,	ypos + al,	1.0,	1.0},
			{xpos,		ypos,		0.0,	0.0}
		};
*/

		x += letra->avance_x >> 6;
		letra_anterior = letra->codigo_unicode;
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLES, 0, posicion_arreglo);
	return x - x_inicial;
}

int Texto::dibujar_texto(int x, int y, std::string texto)
{
	Color negro(0.0, 0.0, 0.0);
	return imprimir_texto(x, y, texto.c_str(), negro, false);
}

int Texto::dibujar_texto(int x, int y, std::string texto, bool centrado)
{
	Color negro(0.0, 0.0, 0.0);
	return imprimir_texto(x, y, texto.c_str(), negro, centrado);
}

int Texto::dibujar_texto(int x, int y, std::string texto, Color color)
{
	return imprimir_texto(x, y, texto.c_str(), color, false);
}

int Texto::dibujar_texto(int x, int y, std::string texto, Color color, bool centrado)
{
	return imprimir_texto(x, y, texto.c_str(), color, centrado);
}

int Texto::ancho_texto_unicode(icu::UnicodeString texto)
{
	int ancho = 0;
	Caracter *letra;
	FT_Bool interletraje = FT_HAS_KERNING(this->tipografia);
	unsigned int letra_anterior = 0;
	for(int n=0; n<texto.length(); n++)
	{
		letra = obtener_caracter((unsigned int)texto[n]);
		if(!letra)
			continue;
		if(interletraje && letra_anterior && letra->codigo_unicode)
		{
			FT_Vector delta;
			FT_Get_Kerning(this->tipografia, letra_anterior, letra->codigo_unicode, FT_KERNING_DEFAULT, &delta);
			ancho += delta.x >> 6;
		}
		ancho += letra->avance_x >> 6;
		letra_anterior = letra->codigo_unicode;
	}
	return ancho;
}

int Texto::ancho_texto(std::string texto)
{
	return ancho_texto_unicode(texto.c_str());
}
