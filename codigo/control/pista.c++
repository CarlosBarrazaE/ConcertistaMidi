#include "pista.h++"

Color Pista::Colores_pista[NUMERO_COLORES_PISTA] = {
	Color(0.0f, 0.598f, 0.0f),
	Color(0.0f, 0.598f, 1.0f),
	Color(1.0f, 0.598f, 1.0f),
	Color(1.0f, 0.424f, 0.0f),
	Color(0.0f, 0.761f, 0.467f),
	Color(0.0f, 0.8, 1.0f),
	Color(1.0f, 0.761f, 0.609f),
	Color(1.0f, 0.761f, 0.0f),
	Color(0.407f, 0.348f, 1.0f)
};

Pista::Pista(std::string instrumento, unsigned int numero_notas, Color color, Modo modo, bool visible, bool sonido)
{
	m_color_pista = color;
	m_modo_pista = modo;
	m_visible = visible;
	m_sonido = sonido;
	m_instrumento = instrumento;
	m_numero_notas = numero_notas;
}

Pista::~Pista()
{
}

void Pista::e_color(Color color)
{
	m_color_pista = color;
}

void Pista::e_modo(Modo modo)
{
	m_modo_pista = modo;
}

void Pista::e_visible(bool estado)
{
	m_visible = estado;
}

void Pista::e_sonido(bool estado)
{
	m_sonido = estado;
}

Color Pista::o_color()
{
	return m_color_pista;
}

Modo Pista::o_modo()
{
	return m_modo_pista;
}

bool Pista::o_visible()
{
	return m_visible;
}

bool Pista::o_sonido()
{
	return m_sonido;
}

std::string Pista::o_instrumento()
{
	return m_instrumento;
}

unsigned int Pista::o_numero_notas()
{
	return m_numero_notas;
}
