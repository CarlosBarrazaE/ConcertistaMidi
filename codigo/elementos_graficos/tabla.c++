#include "tabla.h++"

Tabla::Tabla(int x, int y, int ancho, int alto, unsigned int alto_fila, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_color_fondo(0.9f, 0.9f, 0.9f)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_alto_fila = alto_fila;
	m_fila_seleccionada = 0;//Primera fila predeterminada

	m_espacio_total_columnas = 0;

	m_barra_desplazamiento = new Barra_Desplazamiento(x, y+m_alto_fila, ancho, alto-m_alto_fila, m_alto_fila, 0, recursos);
}

Tabla::~Tabla()
{
	for(Celda c : m_fila_titulo)
		delete c.texto;

	for(Fila *f : m_filas)
		delete f;
}

void Tabla::actualizar_ancho_columnas()
{
	unsigned int posicion_actual = this->x();
	for(Celda c : m_fila_titulo)
	{
		c.texto->posicion(posicion_actual, this->y());
		unsigned int ancho_actual = (c.n_espacio * this->ancho()) / m_espacio_total_columnas;
		c.texto->dimension(ancho_actual, m_alto_fila);
		posicion_actual += ancho_actual;
	}

	for(Fila *f : m_filas)
	{
		f->dimension(this->ancho(), m_alto_fila);

		std::vector<Etiqueta *> *celdas = f->celdas();
		for(unsigned int x = 0; x<m_fila_titulo.size(); x++)
		{
			celdas->at(x)->posicion(m_fila_titulo[x].texto->x(), m_fila_titulo[x].texto->y());
			celdas->at(x)->dimension(m_fila_titulo[x].texto->ancho(), m_fila_titulo[x].texto->alto());
		}
	}
}

void Tabla::actualizar(unsigned int diferencia_tiempo)
{
	m_barra_desplazamiento->actualizar(diferencia_tiempo);
}

void Tabla::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), m_alto_fila, m_color_fondo);

	for(unsigned int x=0; x<m_fila_titulo.size(); x++)
	{
		//m_rectangulo->dibujar(m_fila_titulo[x].texto->x(),m_fila_titulo[x].texto->y(), 10, 40, Color(0.8f, 0.9f, 0.8f));
		m_fila_titulo[x].texto->dibujar();
	}

	m_barra_desplazamiento->dibujar();
	m_rectangulo->dibujar(this->x(), this->y(), 1, this->alto(), m_color_fondo);
	m_rectangulo->dibujar(this->x()+this->ancho()-1, this->y(), 1, this->alto(), m_color_fondo);
}

void Tabla::evento_raton(Raton *raton)
{
	m_barra_desplazamiento->evento_raton(raton);
	for(unsigned int x=0; x<m_filas.size(); x++)
	{
		if(m_filas[x]->esta_seleccionado() && x != m_fila_seleccionada)
		{
			m_filas[m_fila_seleccionada]->deseleccionar();
			m_fila_seleccionada = x;
		}
	}
}

void Tabla::dimension(int ancho, int alto)
{
	this->_dimension(ancho, alto);
	this->actualizar_ancho_columnas();
	//La barra de desplazamiento esta despues de la fila de titulo
	m_barra_desplazamiento->dimension(ancho, alto-m_alto_fila);

	for(Fila *m : m_filas)
		m->dimension(this->ancho(), m_alto_fila);
}

void Tabla::agregar_columna(std::string texto, bool centrado, unsigned int n_espacio)
{
	if(n_espacio == 0)
		n_espacio = 1;
	m_espacio_total_columnas += n_espacio;

	Etiqueta *titulo_celda = new Etiqueta(this->x(), this->y(), centrado, texto, LetraChica, m_recursos);
	titulo_celda->centrado_vertical(true);
	if(!centrado)
		titulo_celda->margen(10);
	Celda celda_actual = {titulo_celda, centrado, n_espacio};

	m_fila_titulo.push_back(celda_actual);

	this->actualizar_ancho_columnas();
}

void Tabla::insertar_fila(std::vector<std::string> texto)
{
	if(texto.size() != m_fila_titulo.size())
	{
		Registro::Error("No coincide el numero de columnas.");
		return;
	}

	int posicion_fila_y = this->y();
	if(m_filas.size() > 0)
		posicion_fila_y = m_filas[m_filas.size()-1]->y()+m_alto_fila;//Obtiene la posicion de la fila anterior

	Fila *f = new Fila(this->x(), posicion_fila_y, this->ancho(), m_alto_fila, m_recursos);
	Etiqueta *nueva_etiqueta;
	for(unsigned int x=0; x<texto.size(); x++)
	{
		nueva_etiqueta = new Etiqueta(m_fila_titulo[x].texto->x(), posicion_fila_y, m_fila_titulo[x].centrado, texto[x], LetraChica, m_recursos);
		nueva_etiqueta->centrado_vertical(true);
		if(!m_fila_titulo[x].centrado)
			nueva_etiqueta->margen(10);
		nueva_etiqueta->dimension(m_fila_titulo[x].texto->ancho(), m_alto_fila);
		f->agregar_celda(nueva_etiqueta);
	}

	m_filas.push_back(f);
	m_barra_desplazamiento->agregar_elemento(f);
}

void Tabla::vaciar()
{
	//Se eliminan las filas al cambiar de carpeta
	m_barra_desplazamiento->vaciar();
	for(Fila *m : m_filas)
		delete m;

	m_filas.clear();
	m_fila_seleccionada = 0;
}

void Tabla::cambiar_seleccion(int cambio)
{
	//Se deselecciona la fila anterior y se marca la siguiente
	//Si llega arriba comienza abajo de nuevo
	if(!m_filas[m_fila_seleccionada]->esta_seleccionado())
	{
		//La fila no esta seleccionada visiblemente
		//hasta que se cambia la seleccion
		m_filas[m_fila_seleccionada]->seleccionar();
	}
	else
	{
		m_filas[m_fila_seleccionada]->deseleccionar();

		if(cambio > 0)
		{
			m_fila_seleccionada++;
			if(m_fila_seleccionada >= m_filas.size())
				m_fila_seleccionada = 0;
		}
		else
		{
			if(m_fila_seleccionada == 0)
				m_fila_seleccionada = m_filas.size() - 1;
			else
				m_fila_seleccionada--;
		}
		m_filas[m_fila_seleccionada]->seleccionar();
	}

	if(m_filas[m_fila_seleccionada]->y() < this->y()+(int)m_alto_fila)
	{
		//Desplaza la barra cuando se sale por arriba
		int inicio_tabla = this->y()+m_alto_fila;
		int inicio_fila = m_filas[m_fila_seleccionada]->y();
		m_barra_desplazamiento->desplazar_y(inicio_tabla - inicio_fila);
	}
	else if(m_filas[m_fila_seleccionada]->y() + m_filas[m_fila_seleccionada]->alto() > this->y()+this->alto())
	{
		//Desplaza la barra cuando se sale por abajo
		int final_tabla = this->y()+this->alto();
		int final_fila = m_filas[m_fila_seleccionada]->y() + m_filas[m_fila_seleccionada]->alto();
		m_barra_desplazamiento->desplazar_y(final_tabla - final_fila);
	}

}

unsigned int Tabla::obtener_seleccion()
{
	return m_fila_seleccionada;
}
