#include "lista_opciones.h++"

Lista_Opciones::Lista_Opciones(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto_seleccion(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_opcion_actual = 0;
	m_ancho_icono = 10;
	m_alto_icono = 10;
	m_centrado_icono = (ancho - m_ancho_icono)/2;
	m_cambio_opcion_seleccionada = false;

	m_texto_seleccion.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_seleccion.posicion(0, 0);
	m_texto_seleccion.dimension(ancho, alto);
	m_texto_seleccion.centrado(true);
}

Lista_Opciones::~Lista_Opciones()
{

}

void Lista_Opciones::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Lista_Opciones::dibujar()
{
	//m_rectangulo->textura(false);
	//m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(1.0f, 0.0f, 1.0f, 0.5f));
	//m_rectangulo->dibujar(this->x(), this->y(), m_ancho_icono, m_alto_icono, Color(0.0f, 1.0f, 1.0f, 0.5f));
	if(m_usar_iconos)
	{
		m_rectangulo->textura(true);
		m_iconos[m_opcion_actual]->activar();
		m_rectangulo->dibujar(this->x()+m_centrado_icono, this->y(), m_ancho_icono, m_alto_icono, Color(1.0f, 1.0f, 1.0f));
	}
	m_texto_seleccion.dibujar();
}

void Lista_Opciones::evento_raton(Raton *raton)
{
	if(raton->x() >= this->x() && raton->x() < this->x() + this->ancho() &&
		raton->y() >= this->y() && raton->y() < this->y() + this->alto())
	{
		if((raton->activado(BotonIzquierdo) || raton->activado(BotonDerecho) || raton->activado(BotonCentral)) && m_sobre_boton)
			m_boton_pre_activado = raton->boton_activado();
		else if(!raton->activado(BotonIzquierdo) && !raton->activado(BotonCentral) && !raton->activado(BotonDerecho))
		{
			m_sobre_boton = true;
			if(m_boton_pre_activado == BotonIzquierdo)
			{
				m_boton_izquierdo = true;
				m_boton_pre_activado = Ninguno;
			}
			else if(m_boton_pre_activado == BotonCentral)
			{
				m_boton_central = true;
				m_boton_pre_activado = Ninguno;
			}
			else if(m_boton_pre_activado == BotonDerecho)
			{
				m_boton_derecho = true;
				m_boton_pre_activado = Ninguno;
			}
		}
	}
	else
	{
		m_sobre_boton = false;
		m_boton_pre_activado = Ninguno;
		m_boton_izquierdo = false;
		m_boton_central = false;
		m_boton_derecho = false;
	}

	if(m_boton_izquierdo)
	{
		m_opcion_actual++;
		if(m_opcion_actual >= m_opciones.size())
			m_opcion_actual = 0;
		m_texto_seleccion.texto(m_opciones[m_opcion_actual]);
		m_cambio_opcion_seleccionada = true;
		m_boton_izquierdo = false;
	}
	else if(m_boton_central)
	{
		m_opcion_actual = m_opciones.size()-1;
		m_texto_seleccion.texto(m_opciones[m_opcion_actual]);
		m_cambio_opcion_seleccionada = true;
		m_boton_central = false;
	}
	else if(m_boton_derecho)
	{
		if(m_opcion_actual == 0)
			m_opcion_actual = m_opciones.size()-1;
		else
			m_opcion_actual--;
		m_texto_seleccion.texto(m_opciones[m_opcion_actual]);
		m_cambio_opcion_seleccionada = true;
		m_boton_derecho = false;
	}
}

void Lista_Opciones::posicion(int x, int y)
{
	this->_posicion(x, y);
	if(m_usar_iconos)
		m_texto_seleccion.posicion(x, y+43);
	else
		m_texto_seleccion.posicion(x, y);
}

void Lista_Opciones::dimension_icono(int ancho, int alto)
{
	m_ancho_icono = ancho;
	m_alto_icono = alto;
	m_centrado_icono = (m_ancho - m_ancho_icono)/2;
}

void Lista_Opciones::opciones_textos(std::vector<std::string> opciones)
{
	m_opciones = opciones;
	m_texto_seleccion.texto(m_opciones[m_opcion_actual]);
}

void Lista_Opciones::opciones_iconos(std::vector<Textura2D*> iconos)
{
	m_iconos = iconos;
	m_usar_iconos = true;
	m_texto_seleccion.dimension(m_texto_seleccion.ancho(), 0);//Para anular centrado vertical
	m_texto_seleccion.posicion(0, 43);//Posicion para iconos
}

void Lista_Opciones::tipografia(Tipografia *tipografia)
{
	m_texto_seleccion.tipografia(tipografia);
}

void Lista_Opciones::opcion_predeterminada(unsigned int opcion)
{
	if(opcion < m_opciones.size())
	{
		m_opcion_actual = opcion;
		m_texto_seleccion.texto(m_opciones[m_opcion_actual]);
	}
}

int Lista_Opciones::opcion_seleccionada()
{
	return m_opcion_actual;
}

bool Lista_Opciones::cambio_opcion_seleccionada()
{
	bool estado = m_cambio_opcion_seleccionada;
	m_cambio_opcion_seleccionada = false;
	return estado;
}
