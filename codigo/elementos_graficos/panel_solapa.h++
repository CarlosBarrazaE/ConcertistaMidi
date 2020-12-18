#ifndef PANEL_SOLAPA_H
#define PANEL_SOLAPA_H

#include <vector>
#include "elemento.h++"
#include "boton.h++"

class Panel_Solapa : public Elemento
{
private:
	//Recursos
	Administrador_Recursos *m_recursos;
	Rectangulo *m_rectangulo;
	Color m_color_normal, m_color_activo;

	//Componentes
	std::vector<Boton*> m_solapas;
	std::vector<std::vector<Elemento *>> m_componentes;

	//Datos
	unsigned int m_solapa_activa;
public:
	Panel_Solapa(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Panel_Solapa();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void agregar_solapa(std::string nombre);
	unsigned int solapa_activa();

	void agregar_elemento_solapa(unsigned int solapa, Elemento *e);
};

#endif
