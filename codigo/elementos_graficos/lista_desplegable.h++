#ifndef LISTA_DESPLEGABLE_H
#define LISTA_DESPLEGABLE_H

#include "elemento.h++"
#include <vector>
#include <string>

class Lista_Desplegable : public Elemento
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Texto *texto;

	std::vector<std::string> opciones;
	std::vector<Textura2D*> iconos;
	bool usar_iconos;
	int ancho_icono, alto_icono;

	bool centrado;
	bool mostrar_lista;
	unsigned int opcion_actual;

	int ajuste_icono;
	int ajuste_texto;
	int centrado_vertical;

	void iniciar(Administrador_Recursos *recursos);
public:
	Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, Texto *texto, Administrador_Recursos *recursos);
	Lista_Desplegable(int x, int y, int ancho, int alto, int ancho_icono, int alto_icono, bool centrado, std::vector<std::string> opciones, std::vector<Textura2D*> iconos, Texto *texto, Administrador_Recursos *recursos);
	~Lista_Desplegable();

	void e_dimension_icono(int ancho, int alto);
	void e_centrado(bool valor);

	void opcion_predeterminada(unsigned int opcion);
	unsigned int opcion_seleccionada();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
};

#endif
