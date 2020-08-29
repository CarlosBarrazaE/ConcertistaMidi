#include "boton.h++"

Boton::Boton(int x, int y, int ancho, int alto, std::string texto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_textura_boton = recursos->textura(T_Boton);

	this->inicializar();

	m_texto.texto(texto);
	m_texto.tipografia(recursos->tipografia(LetraMediana));
	m_texto.posicion(this->x()+this->dx(), this->y()+this->dy());
	m_texto.dimension(ancho, alto);
	m_texto.centrado(true);
}

Boton::Boton(int x, int y, int ancho, int alto, std::string texto, ModeloLetra modelo_letra, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_textura_boton = recursos->textura(T_Boton);

	this->inicializar();

	m_texto.texto(texto);
	m_texto.tipografia(recursos->tipografia(modelo_letra));
	m_texto.posicion(this->x()+this->dx(), this->y()+this->dy());
	m_texto.dimension(ancho, alto);
	m_texto.centrado(true);
}

Boton::~Boton()
{
}

void Boton::inicializar()
{
	m_sobre_boton = false;
	m_boton_pre_activado = false;
	m_boton_activado = false;

	Color color(1.0f, 1.0f, 1.0f);
	m_color_boton_normal = color;
	m_color_boton_actual = color;
	m_color_boton_sobre.color(color.rojo()-0.1f, color.verde()-0.1f, color.azul()-0.1f);
}

void Boton::textura(Textura2D *textura)
{
	m_textura_boton = textura;
}

void Boton::color_boton(Color color)
{
	m_color_boton_normal = color;
	m_color_boton_actual = color;
	m_color_boton_sobre.color(color.rojo()-0.1f, color.verde()-0.1f, color.azul()-0.1f);
}

void Boton::color_texto(Color color)
{
	m_texto.color(color);
}

void Boton::tipografia(Tipografia *tipografia)
{
	m_texto.tipografia(tipografia);
}

void Boton::centrado(bool centrado)
{
	bool centrado_actual = m_centrado;
	m_centrado = centrado;
	if(m_centrado)
	{
		if(!centrado_actual)//Centra el objeto
			this->m_x = this->x() - (this->ancho() / 2.0);
	}
	else
	{
		if(centrado_actual)//Revierte el centrado
			this->m_x = this->x() + (this->ancho() / 2.0);
	}
	m_texto.posicion(this->x()+this->dx(), this->y()+this->dy());
}

void Boton::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Boton::dibujar()
{
	m_textura_boton->activar();
	m_rectangulo->textura(true);
	m_rectangulo->dibujar(this->x()+this->dx(), this->y()+this->dy(), this->ancho(), this->alto(), m_color_boton_actual);

	m_texto.dibujar();
}

void Boton::evento_raton(Raton *raton)
{
	if(raton->x() >= this->x()+this->dx() && raton->x() <= this->x()+this->dx() + this->ancho() &&
		raton->y() >= this->y()+this->dy() && raton->y() <= this->y()+this->dy() + this->alto())
	{
		if(raton->activado(BotonIzquierdo) && m_sobre_boton)
			m_boton_pre_activado = true;
		else if(!raton->activado(BotonIzquierdo))
		{
			m_color_boton_actual = m_color_boton_sobre;
			m_sobre_boton = true;
			if(m_boton_pre_activado)
			{
				m_boton_activado = true;
				m_boton_pre_activado = false;
			}
		}
	}
	else
	{
		m_color_boton_actual = m_color_boton_normal;
		m_sobre_boton = false;
		m_boton_pre_activado = false;
		m_boton_activado = false;
	}
}

void Boton::evento_pantalla(int /*ancho*/, int /*alto*/)
{
	m_texto.posicion(this->x()+this->dx(), this->y()+this->dy());
}

bool Boton::esta_activado()
{
	bool estado = m_boton_activado;
	m_boton_activado = false;
	return estado;
}
