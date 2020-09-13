#include "barra_desplazamiento.h++"
#include "../registro.h++"

Barra_Desplazamiento::Barra_Desplazamiento(int x, int y, int ancho, int alto, int fila, int margen_fila, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto)
{
	m_columna = 0;
	m_margen_columna = 0;
	m_fila = fila;
	m_margen_fila = margen_fila;

	this->inicializar(recursos);
}

Barra_Desplazamiento::Barra_Desplazamiento(int x, int y, int ancho, int alto, int columna, int fila, int margen_columna, int margen_fila, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	m_columna = columna;
	m_fila = fila;
	m_margen_columna = margen_columna;
	m_margen_fila = margen_fila;

	this->inicializar(recursos);
}

Barra_Desplazamiento::~Barra_Desplazamiento()
{
	for(Elemento* e : m_elementos)
		delete e;
	m_elementos.clear();
}

void Barra_Desplazamiento::inicializar(Administrador_Recursos *recursos)
{
	m_alto_actual = 0;
	m_desplazamiento_x = 0;
	m_desplazamiento_y = 0;

	m_calcular_posicion = true;

	m_rectangulo = recursos->figura(F_Rectangulo);
	m_barra = recursos->textura(T_Barra);

	m_sobre_barra = false;
	m_boton_activado = false;
	m_proporcion = 0;

	//Un evento de raton ficticio con una posicion muy lejana
	m_raton_ficticio.actualizar_posicion(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
}

void Barra_Desplazamiento::actualizar_dimension()
{
	int numero_columnas = 1;
	int x_inicio = this->x();
	//Si m_columna es mayor a cero, puede existir mas de una columna y es centrado
	if(m_columna > 0)
	{
		numero_columnas = this->ancho() / (m_columna + m_margen_columna);
		int ancho_actual = (numero_columnas * m_columna) + ((numero_columnas - 1) * m_margen_columna);
		x_inicio = (this->ancho() - ancho_actual) / 2 + this->x();
	}
	int x_actual = x_inicio;
	int y_actual = this->y();
	int contador_columnas = 1;
	for(unsigned int i=0; i<m_elementos.size(); i++)
	{
		m_elementos[i]->posicion(x_actual, y_actual);

		if(contador_columnas < numero_columnas)
		{
			x_actual += m_columna + m_margen_columna;
		}
		else
		{
			contador_columnas = 0;
			x_actual = x_inicio;
			if(i<m_elementos.size()-1)
				y_actual += m_fila + m_margen_fila;
		}
		contador_columnas++;
	}
	m_alto_actual = y_actual + m_fila - this->y();

	m_desplazamiento_y = 0;
	m_calcular_posicion = false;
	if(this->alto() < m_alto_actual)
		m_proporcion = static_cast<double>(this->alto()-20) / static_cast<double>(m_alto_actual);
}

void Barra_Desplazamiento::actualizar(unsigned int diferencia_tiempo)
{
	if(m_calcular_posicion)
		this->actualizar_dimension();
	for(unsigned int i=0; i<m_elementos.size(); i++)
	{
		m_elementos[i]->actualizar(diferencia_tiempo);
	}

	//0.05 de opacidad por fotograma
	if(m_enviar_evento && m_animacion < 1)
		m_animacion += (diferencia_tiempo/1000000000.0) * 3;
	else if(!m_enviar_evento && m_animacion > 0)
		m_animacion -= (diferencia_tiempo/1000000000.0) * 3;
}

void Barra_Desplazamiento::dibujar()
{

	glScissor(this->x(), Pantalla::Alto-this->y()-this->alto(), this->ancho(), this->alto());
	glEnable(GL_SCISSOR_TEST);
	Elemento *e;
	for(unsigned int i=0; i<m_elementos.size(); i++)
	{
		e = m_elementos.at(i);
		if(e->y() + e->alto() > this->y() && e->y() < this->y() + this->alto() &&
			e->x() + e->ancho() > this->x() && e->x() < this->x() + this->ancho())
		{
			e->dibujar();
		}
	}

	if(this->alto() < m_alto_actual)
	{
		m_barra->activar();
		m_rectangulo->extremos_fijos(false, true);
		m_rectangulo->textura(true);
		m_rectangulo->color(Color(0.7f, 0.7f, 0.7f, m_animacion));
		m_rectangulo->dibujar_estirable(this->x()+this->ancho()-10, this->y()+10, 10, this->alto()-20, 0, 10);
		m_rectangulo->color(Color(0.5f, 0.5f, 0.5f, m_animacion));
		m_rectangulo->dibujar_estirable(this->x()+this->ancho()-10, this->y()+10-m_desplazamiento_y*m_proporcion, 10, this->alto() * m_proporcion, 0, 10);
		m_rectangulo->extremos_fijos(false, false);
	}
	glDisable(GL_SCISSOR_TEST);
}

void Barra_Desplazamiento::evento_raton(Raton *raton)
{
	//Solo si el raton esta dentro del espacio del componente se envian el evento
	Raton *evento_raton;
	if(raton->x() >= this->x() && raton->x() < this->x() + this->ancho() &&
		raton->y() >= this->y() && raton->y() < this->y() + this->alto())
	{
		evento_raton = raton;
		m_enviar_evento = true;
	}
	else
		evento_raton = &m_raton_ficticio;

	//Eventos fuera del area no se envian
	if(!m_enviar_evento)
		return;

	//Se envia un evento de raton ficticio solo una vez para desmarcar los componentes
	if(evento_raton == &m_raton_ficticio)
		m_enviar_evento = false;

	int dy = evento_raton->dy();
	int desplazamiento_nuevo_y = 0;
	int desplazamiento_anterior_y = 0;
	if(this->alto() < m_alto_actual)
	{
		desplazamiento_anterior_y = m_desplazamiento_y;
		if(dy != 0)
		{
			//Desplazamiento con ruedita
			m_desplazamiento_y += dy*20;
		}
		else if(evento_raton->x() >= this->x()+this->ancho()-10 && evento_raton->x() <= this->x()+this->ancho() &&
		evento_raton->y() >= this->y()+10 && evento_raton->y() <= this->y() + this->alto()-20)
		{
			//Desplazamiento con clic en la barra
			if(evento_raton->activado(BotonIzquierdo) && m_sobre_barra)
			{
				m_boton_activado = true;
				//El inicio de la barra esta en this->y() + 20, el centro de la barra desplazable esta en (this->alto() * m_proporcion) / 2)
				m_desplazamiento_y = -(evento_raton->y() - (this->y() + 20 + (this->alto() * m_proporcion) / 2)) / m_proporcion;
			}
			else if(!evento_raton->activado(BotonIzquierdo))
				m_sobre_barra = true;
		}
		else if(m_boton_activado)//Desplazamiento arrastrando la barra
			m_desplazamiento_y = -(evento_raton->y() - (this->y() + 20 + (this->alto() * m_proporcion) / 2)) / m_proporcion;
		else
			m_sobre_barra = false;

		if(!evento_raton->activado(BotonIzquierdo) && m_boton_activado)
			m_boton_activado = false;

		if(m_desplazamiento_y > 0)
				m_desplazamiento_y = 0;
		else if(m_desplazamiento_y < this->alto() - m_alto_actual)
			m_desplazamiento_y = this->alto() - m_alto_actual;

		desplazamiento_nuevo_y = m_desplazamiento_y - desplazamiento_anterior_y;
	}

	for(unsigned int i=0; i<m_elementos.size(); i++)
	{
		if(this->alto() < m_alto_actual)
			m_elementos[i]->posicion(m_elementos[i]->x(), m_elementos[i]->y() + desplazamiento_nuevo_y);
		m_elementos[i]->evento_raton(evento_raton);
	}
}

void Barra_Desplazamiento::dimension(int ancho, int alto)
{
	this->_dimension(ancho, alto);
	m_calcular_posicion = true;
}

void Barra_Desplazamiento::desplazar_y(int dy)
{
	int nuevo_desplazamiento = m_desplazamiento_y + dy;
	if(nuevo_desplazamiento > 0)
		nuevo_desplazamiento = 0;
	else if(nuevo_desplazamiento < this->alto() - m_alto_actual)
		nuevo_desplazamiento = this->alto() - m_alto_actual;

	for(unsigned int i=0; i<m_elementos.size(); i++)
	{
		if(this->alto() < m_alto_actual)
			m_elementos[i]->posicion(m_elementos[i]->x(), m_elementos[i]->y() + nuevo_desplazamiento - m_desplazamiento_y);
	}
	m_desplazamiento_y = nuevo_desplazamiento;
}

void Barra_Desplazamiento::agregar_elemento(Elemento *e)
{
	m_elementos.push_back(e);
}

void Barra_Desplazamiento::vaciar()
{
	m_elementos.clear();
	m_calcular_posicion = true;
}
