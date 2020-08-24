#include "tabla.h++"

Tabla::Tabla(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_color_fondo(0.9f, 0.9f, 0.9f)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);
	m_ultima_columna = 0;
	m_ultima_fila = ANCHO_FILA;
	m_fila_seleccionada = 0;//Primera fila predeterminada
}

Tabla::~Tabla()
{
	for(Celda c : m_titulos)
	{
		delete c.texto;
	}
	for(Fila *m : m_filas)
	{
		delete m;
	}
}

void Tabla::actualizar(unsigned int diferencia_tiempo)
{
	for(int x=0; x<m_filas.size(); x++)
	{
		m_filas[x]->actualizar(diferencia_tiempo);
	}
}

void Tabla::dibujar()
{
	//Dibuja solo lo que esta dentro del cuadro
	glScissor(this->x()+this->dx(), Pantalla::Alto-this->y()+this->dy()-this->alto(), this->ancho(), this->alto());
	glEnable(GL_SCISSOR_TEST);
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x()+this->dx(), this->y()+this->dy(), this->ancho(), ANCHO_FILA, m_color_fondo);

	for(int x=0; x<m_titulos.size(); x++)
	{
		m_rectangulo->dibujar(m_titulos[x].texto->x(),m_titulos[x].texto->y(), 10, 40, Color(0.4f, 0.2f, 0.4f));
		m_titulos[x].texto->dibujar();
	}

	for(int x=0; x<m_filas.size(); x++)
	{
		if(m_filas[x]->y() < this->y()+this->alto())
			m_filas[x]->dibujar();
	}
	glDisable(GL_SCISSOR_TEST);
}

void Tabla::evento_raton(Raton *raton)
{
	for(int x=0; x<m_filas.size(); x++)
	{
		if(m_filas[x]->y() < this->y()+this->alto())
		{
			m_filas[x]->evento_raton(raton);
			if(m_filas[x]->esta_seleccionado() && x != m_fila_seleccionada)
			{
				m_filas[m_fila_seleccionada]->deseleccionar();
				m_fila_seleccionada = x;
			}
		}
	}
}

void Tabla::evento_pantalla(int ancho, int alto)
{

}

void Tabla::agregar_columna(std::string nombre, double ancho)
{
	if(ancho > 1)
		ancho = 1;
	else if(ancho < 0)
		ancho = 0;

	Celda celda_actual = {new Etiqueta(this->x()+m_ultima_columna, this->y(), false, nombre, LetraChica, m_recursos), ancho};

	m_ultima_columna = m_ultima_columna+this->ancho()*ancho;

	m_titulos.push_back(celda_actual);
}

void Tabla::insertar_fila(std::vector<std::string> fila_contenido)
{
	if(fila_contenido.size() == m_titulos.size())
	{
		Fila *fila_nueva = new Fila(this->x(), this->y()+m_ultima_fila, this->ancho(), ANCHO_FILA-1, m_recursos);
		for(int x=0; x<fila_contenido.size(); x++)
		{
			fila_nueva->agregar_celda(new Etiqueta(m_titulos[x].texto->x(), this->y()+m_ultima_fila, false, fila_contenido[x], LetraChica, m_recursos));
		}
		m_filas.push_back(fila_nueva);
		m_ultima_fila += ANCHO_FILA;
	}
	else
		Registro::Error("No coincide el numero de columnas en la tabla");
}

void Tabla::eliminar_contenido()
{
	//Se eliminan las filas al cambiar de carpeta
	for(Fila *m : m_filas)
	{
		delete m;
	}
	m_filas.clear();
	m_ultima_fila = ANCHO_FILA;
}

int Tabla::obtener_seleccion()
{
	return m_fila_seleccionada;
}
