#include "lista_desplegable.h++"

Lista_Desplegable::Lista_Desplegable(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto_seleccion(recursos)
{
	m_rectangulo = recursos->obtener_figura(F_Rectangulo);
	m_opcion_actual = 0;
	m_mostrar_lista = false;
	m_ancho_icono = 10;
	m_alto_icono = 10;
	m_centrado_icono = (ancho - m_ancho_icono)/2;

	m_texto_seleccion.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_seleccion.posicion(x, y);
	m_texto_seleccion.dimension(ancho, alto);
	m_texto_seleccion.centrado(true);
}

Lista_Desplegable::~Lista_Desplegable()
{

}

void Lista_Desplegable::dimension_icono(int ancho, int alto)
{
	m_ancho_icono = ancho;
	m_alto_icono = alto;
	m_centrado_icono = (m_ancho - m_ancho_icono)/2;
}

void Lista_Desplegable::opciones_textos(std::vector<std::string> opciones)
{
	m_opciones = opciones;
	m_texto_seleccion.texto(opciones[m_opcion_actual]);
}

void Lista_Desplegable::opciones_iconos(std::vector<Textura2D*> iconos)
{
	m_iconos = iconos;
	m_usar_iconos = true;
	m_texto_seleccion.alto(0);//Para anular centrado vertical
}

void Lista_Desplegable::tipografia(Tipografia *tipografia)
{
	m_tipografia = tipografia;
	m_texto_seleccion.tipografia(m_tipografia);
}

void Lista_Desplegable::opcion_predeterminada(unsigned int opcion)
{
	if(opcion >= 0 && opcion < m_opciones.size())
		m_opcion_actual = opcion;
}

unsigned int Lista_Desplegable::opcion_seleccionada()
{
	return m_opcion_actual;
}

void Lista_Desplegable::actualizar(unsigned int diferencia_tiempo)
{
	if(m_usar_iconos)
	{
		m_texto_seleccion.posicion(this->posicion_x() + this->dx(), this->posicion_y() + this->dy()+47);
	}
	else
	{
		m_texto_seleccion.posicion(this->posicion_x() + this->dx(), this->posicion_y() + this->dy());
	}
}

void Lista_Desplegable::dibujar()
{
	m_rectangulo->textura(false);
	//m_rectangulo->dibujar(this->posicion_x()+this->dx(), this->posicion_y()+this->dy(), this->ancho(), this->alto(), Color(1.0f, 0.0f, 1.0f, 0.5f));
	//m_rectangulo->dibujar(this->posicion_x()+this->dx(), this->posicion_y()+this->dy(), m_ancho_icono, m_alto_icono, Color(0.0f, 1.0f, 1.0f, 0.5f));
	if(m_usar_iconos)
	{
		m_rectangulo->textura(true);
		m_iconos[m_opcion_actual]->activar();
		m_rectangulo->dibujar(this->posicion_x()+this->dx()+m_centrado_icono, this->posicion_y()+this->dy(), m_ancho_icono, m_alto_icono, Color(1.0f, 1.0f, 1.0f));
	}
	m_texto_seleccion.dibujar();
	if(m_mostrar_lista)
	{
	}
}

void Lista_Desplegable::evento_raton(Raton *raton)
{
}

void Lista_Desplegable::evento_pantalla(int ancho, int alto)
{
}
