#ifndef ADMINISTRADOR_DE_RECURSOS_H
#define ADMINISTRADOR_DE_RECURSOS_H

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sombreador.h++"
#include "textura_2d.h++"
#include "texto.h++"
#include "color.h++"

#include "../archivos/archivo.h++"
#include "../archivos/imagen_tga.h++"

#include "../registro.h++"

enum Textura
{
	T_Titulo,
	T_Boton
};

enum SombreadorVF
{
	Rectangulo_Textura,
	Rectangulo_SinTextura,
	Rectangulo_Texto
};

enum ModeloLetra
{
	LetraTitulo = 0,
	LetraGrande,
	LetraMediana,
	LetraChica,
	LetraMuyChica,
	NumeroElementos
};

class Administrador_Recursos
{
private:
	std::map<Textura, Textura2D*> lista_texturas;
	std::map<unsigned int, Textura2D*> lista_caracteres;
	std::map<SombreadorVF, Sombreador*> lista_sombreadores;

	std::map<Textura, const char*> archivo_texturas;
	std::map<SombreadorVF, const char*> archivo_sombreador_vertice;
	std::map<SombreadorVF, const char*> archivo_sombreador_fragmento;

	Texto *formato_letras[NumeroElementos];//Una por cada Modelo de letra

	int ancho = 800;
	int alto = 600;
	glm::mat4 matriz_proyeccion;
public:
	Administrador_Recursos();
	~Administrador_Recursos();

	Textura2D *obtener_textura(Textura valor);
	void activar_textura(Textura valor);

	Sombreador *obtener_sombreador(SombreadorVF valor);
	void activar_sombreador(SombreadorVF valor);

	Texto *obtener_tipografia(ModeloLetra tipo);
	int mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto);
	int mostrar_texto(int x, int y, ModeloLetra tipo, std::string texto, Color color);

	void actualizar_pantalla(int ancho, int alto);
};

#endif
