#ifndef TABLA_H
#define TABLA_H

#define ANCHO_FILA 40

#include "elemento.h++"
#include "etiqueta.h++"
#include "fila.h++"
#include "barra_desplazamiento.h++"
#include "../dispositivos/pantalla.h++"

#include <vector>

struct Celda
{
	//TODO posiblemente deberia agregar un campo para saber si es ocultable cuando la tabla es muy chica
	//Agregar Aliniacion del texto (centrado por ejemplo)
	Etiqueta *texto;
	double ancho_celda;//Porcentaje reprecentado de 0 a 1 en relacion al ancho de la fila
};

class Tabla : public Elemento
{
private:
	Administrador_Recursos *m_recursos;
	std::vector<Celda> m_titulos;//Fila titulo
	std::vector<Fila*> m_filas;

	unsigned int m_fila_seleccionada;

	//Etiqueta m_textos;
	Rectangulo *m_rectangulo;
	Color m_color_fondo;
	Barra_Desplazamiento *m_barra_desplazamiento;

	int m_ultima_columna;
	int m_ultima_fila;

public:
	Tabla(int x, int y, int ancho, int alto, Administrador_Recursos *recursos);
	~Tabla();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(int ancho, int alto) override;

	void agregar_columna(std::string nombre, double ancho);
	void insertar_fila(std::vector<std::string> fila_contenido);
	void vaciar();

	void cambiar_seleccion(int cambio);
	unsigned int obtener_seleccion();
};

#endif
