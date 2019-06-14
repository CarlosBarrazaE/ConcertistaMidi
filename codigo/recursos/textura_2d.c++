#include "textura_2d.h++"
#include <iostream>
unsigned int Textura2D::ultimo_indice_seleccionado = 0;

Textura2D::Textura2D()
{
	this->ancho = 0;
	this->alto = 0;
	this->formato = 0;
	this->envolver_s = GL_REPEAT;
	this->envolver_t = GL_REPEAT;
	this->filtro_minimizar = GL_NEAREST;
	this->filtro_maximizar = GL_LINEAR;

	glGenTextures(1, &this->indice_textura);
}

Textura2D::~Textura2D()
{
}

unsigned int Textura2D::o_indice()
{
	return this->indice_textura;
}

void Textura2D::generar(unsigned int ancho, unsigned int alto, unsigned int bits, unsigned int formato_entrada, unsigned char *datos)
{
	this->ancho = ancho;
	this->alto = alto;

	if(bits == 24)
		this->formato = GL_RGB;
	else
		this->formato = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, this->indice_textura);
	glTexImage2D(GL_TEXTURE_2D, 0, this->formato, ancho, alto, 0, this->formato, GL_UNSIGNED_BYTE, datos);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->envolver_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->envolver_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filtro_minimizar);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filtro_maximizar);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Textura2D::activar()
{
	if(Textura2D::ultimo_indice_seleccionado != this->indice_textura)
	{
		Textura2D::ultimo_indice_seleccionado = this->indice_textura;
		glBindTexture(GL_TEXTURE_2D, this->indice_textura);
	}
}

void Textura2D::e_envolver_horizontal(unsigned int valor)
{
	this->envolver_s = valor;
}

void Textura2D::e_envolver_vertical(unsigned int valor)
{
	this->envolver_t = valor;
}

void Textura2D::e_filtro_minimizar(unsigned int valor)
{
	this->filtro_minimizar = valor;
}

void Textura2D::e_filtro_maximizar(unsigned int valor)
{
	this->filtro_maximizar = valor;
}
