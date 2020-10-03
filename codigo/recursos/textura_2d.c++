#include "textura_2d.h++"

unsigned int Textura2D::Ultimo_indice_seleccionado = 0;

Textura2D::Textura2D()
{
	m_ancho = 0;
	m_alto = 0;
	m_formato = 0;
	m_envolver_s = GL_CLAMP_TO_EDGE;
	m_envolver_t = GL_CLAMP_TO_EDGE;
	m_filtro_minimizar = GL_LINEAR;
	m_filtro_maximizar = GL_LINEAR;

	glGenTextures(1, &m_indice_textura);
	//GL_CLAMP_TO_EDGE GL_REPEAT
	//GL_LINEAR GL_NEAREST
}

Textura2D::~Textura2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &m_indice_textura);
	Textura2D::Ultimo_indice_seleccionado = 0;
}

void Textura2D::generar(int ancho, int alto, unsigned int bits, unsigned char *datos)
{
	m_ancho = ancho;
	m_alto = alto;

	if(bits == 24)
		m_formato = GL_RGB;
	else
		m_formato = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, m_indice_textura);
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(m_formato), ancho, alto, 0, m_formato, GL_UNSIGNED_BYTE, datos);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_envolver_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_envolver_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filtro_minimizar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filtro_maximizar);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Textura2D::activar()
{
	if(Textura2D::Ultimo_indice_seleccionado != m_indice_textura)
	{
		Textura2D::Ultimo_indice_seleccionado = m_indice_textura;
		glBindTexture(GL_TEXTURE_2D, m_indice_textura);
	}
}

void Textura2D::envolver_horizontal(int valor)
{
	m_envolver_s = valor;
	this->activar();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_envolver_s);
}

void Textura2D::envolver_vertical(int valor)
{
	m_envolver_t = valor;
	this->activar();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_envolver_t);
}

void Textura2D::envolver(int s, int t)
{
	m_envolver_s = s;
	m_envolver_t = t;
	this->activar();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_envolver_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_envolver_t);
}

void Textura2D::filtro_minimizar(int valor)
{
	m_filtro_minimizar = valor;
	this->activar();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filtro_minimizar);
}

void Textura2D::filtro_maximizar(int valor)
{
	m_filtro_maximizar = valor;
	this->activar();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filtro_maximizar);
}
