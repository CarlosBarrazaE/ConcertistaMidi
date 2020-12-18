#include "panel_solapa.h++"

Panel_Solapa::Panel_Solapa(float x, float y, float ancho, float alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_solapa_activa = 0;
	m_color_normal = Color(1.0f, 1.0f, 1.0f);
	m_color_activo = Color(0.9f, 0.9f, 0.9f);
	m_solapa_activa = 0;
}

Panel_Solapa::~Panel_Solapa()
{
	for(Boton *b : m_solapas)
		delete b;
}

void Panel_Solapa::actualizar(unsigned int diferencia_tiempo)
{
	if(m_componentes.size() > m_solapa_activa)
	{
		for(long unsigned int y=0; y<m_componentes[m_solapa_activa].size(); y++)
		{
			m_componentes[m_solapa_activa][y]->actualizar(diferencia_tiempo);
		}
	}
}

void Panel_Solapa::dibujar()
{
	m_rectangulo->dibujar(0, 40, this->ancho(), this->alto() - 80, Color(1.0f, 1.0f, 1.0f));//Fondo blanco
	for(Boton *b : m_solapas)
		b->dibujar();
	if(m_componentes.size() > m_solapa_activa)
	{
		for(long unsigned int y=0; y<m_componentes[m_solapa_activa].size(); y++)
			m_componentes[m_solapa_activa][y]->dibujar();
	}
}

void Panel_Solapa::evento_raton(Raton *raton)
{
	for(long unsigned int x=0; x<m_solapas.size(); x++)
	{
		m_solapas[x]->evento_raton(raton);
		if(m_solapas[x]->esta_activado())
		{
			m_solapas[m_solapa_activa]->color_boton(m_color_normal);
			m_solapas[x]->color_boton(m_color_activo);
			m_solapa_activa = static_cast<unsigned int>(x);
		}
	}
	if(m_componentes.size() > m_solapa_activa)
	{
		for(long unsigned int y=0; y<m_componentes[m_solapa_activa].size(); y++)
			m_componentes[m_solapa_activa][y]->evento_raton(raton);
	}
}

void Panel_Solapa::agregar_solapa(std::string nombre)
{
	m_solapas.push_back(new Boton(this->x()+10, this->y()+10+static_cast<float>(m_solapas.size())*50.0f, 230, 50, nombre, LetraMediana, m_recursos));
	if(m_solapas.size() == 1)
		m_solapas[m_solapas.size()-1]->color_boton(m_color_activo);
	else
		m_solapas[m_solapas.size()-1]->color_boton(m_color_normal);
	m_componentes.push_back(std::vector<Elemento*>());
}

unsigned int Panel_Solapa::solapa_activa()
{
	return m_solapa_activa;
}

void Panel_Solapa::agregar_elemento_solapa(unsigned int solapa, Elemento *e)
{
	if(m_solapas.size() > solapa && m_componentes.size() > solapa)
	{
		m_componentes[solapa].push_back(e);
	}
}
