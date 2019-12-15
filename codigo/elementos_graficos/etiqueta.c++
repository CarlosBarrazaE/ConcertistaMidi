#include "etiqueta.h++"

Etiqueta::Etiqueta() : Elemento(0, 0, 0, 0)
{
}

Etiqueta::Etiqueta(int x, int y, int ancho, int alto, bool centrado, std::string texto, Texto *tipografia) : Elemento(x, y, ancho, alto, centrado)
{
	m_texto = texto;
	m_tipografia = tipografia;
}

Etiqueta::Etiqueta(int x, int y, bool centrado, std::string texto, Texto *tipografia) : Elemento(x, y, 0, 0, centrado)
{
	m_texto = texto;
	m_tipografia = tipografia;
}

Etiqueta::~Etiqueta()
{

}

void Etiqueta::actualizar(unsigned int diferencia_tiempo)
{
}

void Etiqueta::dibujar()
{
	if(m_centrado)
	{
		if(this->alto() == 0)
			m_tipografia->imprimir(this->posicion_x()+this->dx()+this->ancho()/2.0 - m_largo_texto / 2.0, this->posicion_y()+this->dy()+m_tipografia->alto_texto(), m_texto, m_color);
		else
			m_tipografia->imprimir(this->posicion_x()+this->dx()+this->ancho()/2.0 - m_largo_texto / 2.0, this->posicion_y()+this->dy()+m_tipografia->alto_texto()+this->alto()/2.0-m_tipografia->alto_texto()/2.0, m_texto, m_color);
	}
	else
		m_tipografia->imprimir(this->posicion_x()+this->dx(), this->posicion_y()+this->dy()+m_tipografia->alto_texto(), m_texto, m_color);
}

void Etiqueta::evento_raton(Raton *raton)
{
}

void Etiqueta::evento_pantalla(int ancho, int alto)
{
}

void Etiqueta::texto(std::string texto)
{
	m_texto = texto;
	if(m_tipografia != NULL)
	{
		m_largo_texto = m_tipografia->ancho_texto(m_texto);
		m_alto_texto = m_tipografia->alto_texto();
	}
	else
	{
		m_largo_texto = 0;
		m_alto_texto = 0;
	}
}

void Etiqueta::color(Color color)
{
	m_color = color;
}

void Etiqueta::tipografia(Texto *tipografia)
{
	m_tipografia = tipografia;
	m_largo_texto = m_tipografia->ancho_texto(m_texto);
	m_alto_texto = m_tipografia->alto_texto();
}

void Etiqueta::tamanno_letra()
{
}

void Etiqueta::centrado(bool centrado)
{
	m_centrado = centrado;
}

int Etiqueta::largo_texto()
{
	return m_largo_texto;
}

int Etiqueta::alto_texto()
{
	return m_alto_texto;
}
