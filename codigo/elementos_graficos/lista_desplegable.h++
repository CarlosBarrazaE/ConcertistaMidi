#ifndef LISTA_DESPLEGABLE_H
#define LISTA_DESPLEGABLE_H

#include "elemento.h++"
#include "etiqueta.h++"
#include <vector>
#include <string>

class Lista_Desplegable : public Elemento
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Tipografia *m_tipografia;//TODO ¿sera necesario?
	Etiqueta m_texto_seleccion;

	std::vector<std::string> m_opciones;
	std::vector<Textura2D*> m_iconos;
	bool m_usar_iconos = false;
	bool m_mostrar_lista;

	int m_centrado_icono;
	int m_ancho_icono, m_alto_icono;
	unsigned int m_opcion_actual;
public:
	Lista_Desplegable(int x, int y, int ancho, int alto, Administrador_Recursos *recursos);
	~Lista_Desplegable();

	void dimension_icono(int ancho, int alto);
	void opciones_textos(std::vector<std::string> opciones);
	void opciones_iconos(std::vector<Textura2D*> iconos);
	void tipografia(Tipografia *tipografia);
	void opcion_predeterminada(unsigned int opcion);
	unsigned int opcion_seleccionada();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
	void evento_pantalla(int ancho, int alto);
};

#endif
