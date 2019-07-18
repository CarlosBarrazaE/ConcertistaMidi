#ifndef LISTA_DESPLEGABLE_H
#define LISTA_DESPLEGABLE_H

#include "elemento.h++"
#include <vector>
#include <string>

class Lista_Desplegable : public Elemento
{
private:
	std::vector<std::string> opciones;
	std::vector<Textura2D*> iconos;
	bool usar_iconos;
	unsigned int opcion_actual;

public:
	Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, Administrador_Recursos *recursos);
	Lista_Desplegable(int x, int y, int ancho, int alto, std::vector<std::string> opciones, std::vector<Textura2D*> iconos, Administrador_Recursos *recursos);
	~Lista_Desplegable();

	void opcion_predeterminada(unsigned int opcion);
	unsigned int opcion_seleccionada();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
};

#endif
