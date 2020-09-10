#ifndef TABLA_H
#define TABLA_H

#include "elemento.h++"
#include "etiqueta.h++"
#include "fila.h++"
#include "barra_desplazamiento.h++"
#include "../dispositivos/pantalla.h++"

#include <vector>

struct Celda
{
	//TODO posiblemente deberia agregar un campo para saber si es ocultable cuando la tabla es muy chica
	Etiqueta *texto;
	bool centrado;
	unsigned int n_espacio;//Porcentaje reprecentado de 0 a 1 en relacion al ancho de la fila
};

class Tabla : public Elemento
{
private:
	Administrador_Recursos *m_recursos;
	std::vector<Celda> m_fila_titulo;//Fila titulo
	std::vector<Fila*> m_filas;

	unsigned int m_alto_fila;
	unsigned int m_fila_seleccionada;

	//Etiqueta m_textos;
	Rectangulo *m_rectangulo;
	Color m_color_fondo;
	Barra_Desplazamiento *m_barra_desplazamiento;

	unsigned int m_espacio_total_columnas;

	void actualizar_ancho_columnas();

public:
	Tabla(int x, int y, int ancho, int alto, unsigned int alto_fila, Administrador_Recursos *recursos);
	~Tabla();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(int ancho, int alto) override;

	void agregar_columna(std::string texto, bool centrado, unsigned int n_espacio);
	void insertar_fila(std::vector<std::string> texto);
	void vaciar();

	void cambiar_seleccion(int cambio);
	unsigned int obtener_seleccion();
};

#endif
