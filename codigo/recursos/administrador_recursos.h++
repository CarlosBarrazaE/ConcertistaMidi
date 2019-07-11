#ifndef ADMINISTRADOR_DE_RECURSOS_H
#define ADMINISTRADOR_DE_RECURSOS_H

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sombreador.h++"
#include "textura_2d.h++"
#include "texto.h++"
#include "color.h++"
#include "rectangulo.h++"

#include "../archivos/archivo.h++"
#include "../archivos/imagen_tga.h++"

#include "../registro.h++"

enum Textura
{
	T_FondoTitulo,
	T_Titulo,
	T_Boton,
	T_TeclaBlanca,
	T_TeclaNegra,
	T_TeclaBlancaPresionada,
	T_TeclaBlancaPresionadaDoble,
	T_TeclaNegraPresionada,
	T_BordeOrganoRojo,
	T_BordeOrganoNegro,
	T_Nota,
	T_Sombra,
	T_FrenteBarraProgreso,
	T_ParticulaNota,
};

enum SombreadorVF
{
	S_Rectangulo,
	S_Texto,
	S_Particula,
};

enum FiguraGeometrica
{
	F_Rectangulo,
};

enum ModeloLetra
{
	LetraTitulo = 0,
	LetraGrande,
	LetraMediana,
	LetraChica,
	LetraMuyChica,
};

class Administrador_Recursos
{
private:
	std::map<Textura, Textura2D*> lista_texturas;
	std::map<SombreadorVF, Sombreador*> lista_sombreadores;
	std::map<FiguraGeometrica, Rectangulo*> lista_figuras;

	std::map<Textura, const char*> archivo_texturas;
	std::map<SombreadorVF, const char*> archivo_sombreador_vertice;
	std::map<SombreadorVF, const char*> archivo_sombreador_fragmento;

	std::map<ModeloLetra, Texto*> formato_letras;

	int ancho;
	int alto;
	glm::mat4 matriz_proyeccion;
public:
	Administrador_Recursos();
	~Administrador_Recursos();

	Textura2D *obtener_textura(Textura valor);
	Sombreador *obtener_sombreador(SombreadorVF valor);
	Rectangulo *obtener_figura(FiguraGeometrica valor);
	Texto *obtener_tipografia(ModeloLetra tipo);

	void actualizar_pantalla(int ancho, int alto);
};

#endif
