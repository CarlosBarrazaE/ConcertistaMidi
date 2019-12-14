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
	T_Barra,
	T_ConfiguracionPista,
	T_SonidoActivado,
	T_SonidoDesactivado,
	T_Reproducir,
	T_Pausar,
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
	std::map<Textura, Textura2D*> m_lista_texturas;
	std::map<SombreadorVF, Sombreador*> m_lista_sombreadores;
	std::map<FiguraGeometrica, Rectangulo*> m_lista_figuras;

	std::map<Textura, const char*> m_archivo_texturas;
	std::map<SombreadorVF, const char*> m_archivo_sombreador_vertice;
	std::map<SombreadorVF, const char*> m_archivo_sombreador_fragmento;

	std::map<ModeloLetra, Texto*> m_formato_letras;

	int m_ancho;
	int m_alto;
	glm::mat4 m_matriz_proyeccion;
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
