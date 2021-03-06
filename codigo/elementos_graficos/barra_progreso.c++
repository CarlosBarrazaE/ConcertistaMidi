#include "barra_progreso.h++"

Barra_Progreso::Barra_Progreso(float x, float y, float ancho, float alto, microseconds_t tiempo_total, MidiEventMicrosecondList lineas, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto), m_texto_inicial(recursos), m_texto_final(recursos), m_color_fondo(0.8f, 0.8f, 0.8f), m_color_progreso(0.0f, 0.761f, 0.467f)
{
	m_tiempo_total = tiempo_total;
	m_tiempo_actual = 0;
	m_lineas = lineas;
	m_tiempo_nuevo = -1;
	m_sobre_barra = false;
	m_x_anterior = 0;

	m_frente = recursos->textura(T_FrenteBarraProgreso);
	m_textura_sombra = recursos->textura(T_Sombra);
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_texto_inicial.texto(Funciones::microsegundo_a_texto(m_tiempo_actual, true));
	m_texto_inicial.tipografia(recursos->tipografia(LetraMuyChica));
	m_texto_inicial.posicion(this->x()+4, this->y() + this->alto() - 12);
	m_texto_inicial.color(Color(0.0f, 0.0f, 0.0f));

	m_texto_final.texto(Funciones::microsegundo_a_texto(tiempo_total, true));
	m_texto_final.tipografia(recursos->tipografia(LetraMuyChica));
	m_texto_final.posicion(this->x()+this->ancho() - (4 + m_texto_final.largo_texto()), this->y() + this->alto() - 12);
	m_texto_final.color(Color(0.0f, 0.0f, 0.0f));
}

Barra_Progreso::~Barra_Progreso()
{
}

void Barra_Progreso::actualizar(unsigned int /*diferencia_tiempo*/)
{
	m_progreso = (static_cast<float>(m_tiempo_actual) / static_cast<float>(m_tiempo_total)) * this->ancho();
	if(m_progreso > this->ancho())
		m_progreso = this->ancho();
	else if(m_progreso < 0)
		m_progreso = 0;

	m_texto_inicial.texto(Funciones::microsegundo_a_texto(m_tiempo_actual, true));
}

void Barra_Progreso::dibujar()
{
	//Dibuja el fondo (progreso/fondo)
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), m_progreso, this->alto(), m_color_progreso);
	m_rectangulo->dibujar(this->x()+m_progreso, this->y(), this->ancho() - m_progreso, this->alto(), m_color_fondo);

	//Dibuja las lineas verticales
	m_rectangulo->color(Color(0.5f, 0.5f, 0.5f));
	for(unsigned int i=0; i<m_lineas.size(); i++)
	{
		m_rectangulo->dibujar((static_cast<float>(m_lineas[i]) / static_cast<float>(m_tiempo_total)) * this->ancho(), this->y(), 1, this->alto());
	}

	//Dibuja los bordes de arriba y abajo
	m_rectangulo->color(Color(0.15f, 0.15f, 0.15f));
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), 1);
	m_rectangulo->dibujar(this->x(), this->y()+this->alto()-1, this->ancho(), 1);

	//Dibuja el brillo
	m_frente->activar();
	m_rectangulo->textura(true);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(1.0f, 1.0f, 1.0f));

	//Dibuja el tiempo inicial y el tiempo restante
	m_texto_inicial.dibujar();
	m_texto_final.dibujar();

	//Dibuja la sombra
	m_textura_sombra->activar();
	m_rectangulo->color(Color(0.7f, 0.7f, 0.7f));
	m_rectangulo->dibujar(this->x(), this->y()+this->alto(), this->ancho(), 20);
}

void Barra_Progreso::evento_raton(Raton *raton)
{
	if(raton->esta_sobre(this->x(), this->y(), this->ancho(), this->alto()))
	{
		if(raton->activado(BotonIzquierdo) && m_sobre_barra)
		{
			if(m_x_anterior != raton->x() || m_tiempo_nuevo == -1)
			{
				m_x_anterior = raton->x();
				m_tiempo_nuevo = static_cast<microseconds_t>((static_cast<float>(raton->x()) / static_cast<float>(this->ancho())) * static_cast<float>(m_tiempo_total));
			}
		}
		else if(!raton->activado(BotonIzquierdo))
		{
			m_sobre_barra = true;

			//Cambio de tiempo con la ruedita del raton
			if(raton->dy() < 0)
			{
				if(m_tiempo_actual > 1000000)
					m_tiempo_nuevo = m_tiempo_actual-1000000;
				else
					m_tiempo_nuevo = 0;
			}
			else if(raton->dy() > 0)
			{
				if(m_tiempo_actual+1000000 > m_tiempo_total)
					m_tiempo_nuevo = m_tiempo_total;
				else
					m_tiempo_nuevo = m_tiempo_actual+1000000;
			}
		}

	}
	else
	{
		m_sobre_barra = false;
	}
}

void Barra_Progreso::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
	m_texto_final.posicion(ancho - (4 + m_texto_final.largo_texto()), this->y() + this->alto() - 12);
}

void Barra_Progreso::tiempo(microseconds_t tiempo_actual)
{
	if(tiempo_actual < 0)
		m_tiempo_actual = 0;
	else
		m_tiempo_actual = tiempo_actual;
}

microseconds_t Barra_Progreso::tiempo_seleccionado()
{
	microseconds_t tiempo_actual = m_tiempo_nuevo;
	m_tiempo_nuevo = -1;
	return tiempo_actual;
}
