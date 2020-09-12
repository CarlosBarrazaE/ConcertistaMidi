#include "figura.h++"

unsigned int Figura::Ultimo_indice_seleccionado = 0;

Figura::Figura(Sombreador *sombreador)
{
	this->m_sombreador = sombreador;

	m_indice_figura = 0;//Matriz de vertice de objeto
	glGenVertexArrays(1, &m_indice_figura);
	glBindVertexArray(m_indice_figura);
	Figura::Ultimo_indice_seleccionado = m_indice_figura;
}

Figura::~Figura()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_indice_figura);
	Figura::Ultimo_indice_seleccionado = 0;
}

void Figura::seleccionar_figura()
{
	if(Figura::Ultimo_indice_seleccionado != m_indice_figura)
	{
		glBindVertexArray(m_indice_figura);
		Figura::Ultimo_indice_seleccionado = m_indice_figura;
	}
}
