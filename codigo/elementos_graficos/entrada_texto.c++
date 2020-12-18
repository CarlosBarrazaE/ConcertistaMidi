#include "entrada_texto.h++"

Entrada_Texto::Entrada_Texto(float x, float y, float ancho, float alto, std::string /*texto*/, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto_mostrado(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_texto_mostrado.tipografia(recursos->tipografia(LetraMediana));
	m_texto_mostrado.posicion(this->x()+10, this->y());

	m_cursor = true;
	m_tiempo_cursor = 0;
	m_posicion_cursor = 0;
}

Entrada_Texto::~Entrada_Texto()
{
}

void Entrada_Texto::actualizar(unsigned int diferencia_tiempo)
{
	m_tiempo_cursor += static_cast<float>(diferencia_tiempo) / 1000000000.0f;
	if(m_tiempo_cursor >= 1)//1 Segundo
	{
		m_cursor = !m_cursor;
		m_tiempo_cursor = 0.0f;
	}
}

void Entrada_Texto::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(1.0f, 0.75f, 0.85f));

	m_texto_mostrado.dibujar();

	if(m_cursor)
		m_rectangulo->dibujar(this->x()+m_posicion_cursor+10, this->y()+5, 1, this->alto()-10, Color(0.0f, 0.0f, 0.0f));
}

void Entrada_Texto::evento_raton(Raton */*raton*/)
{
}

void Entrada_Texto::evento_texto(std::string texto)
{
	m_ptexto += texto;
	m_texto_mostrado.texto(m_ptexto);
	m_posicion_cursor = m_texto_mostrado.largo_texto()+2;
}
