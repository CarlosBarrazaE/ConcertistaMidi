#include "ruta_exploracion.h++"

Ruta_Exploracion::Ruta_Exploracion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_boton_atraz = new Boton(x, y, 30, 30, "<", recursos);
	m_boton_atraz->color_boton(Color(1.0f, 1.0f, 1.0f));

	m_boton_adelante = new Boton(x+30, y, 30, 30, ">", recursos);
	m_boton_adelante->color_boton(Color(1.0f, 1.0f, 1.0f));
}

Ruta_Exploracion::~Ruta_Exploracion()
{
	delete m_boton_atraz;
	delete m_boton_adelante;

	for(Boton *b : m_carpetas)
		delete b;
}

void Ruta_Exploracion::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Ruta_Exploracion::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(0.5f, 0.47f, 0.86f));

	m_boton_atraz->dibujar();
	m_boton_adelante->dibujar();
}

void Ruta_Exploracion::evento_raton(Raton *raton)
{
	m_boton_atraz->evento_raton(raton);
	m_boton_adelante->evento_raton(raton);
}

void Ruta_Exploracion::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
}
