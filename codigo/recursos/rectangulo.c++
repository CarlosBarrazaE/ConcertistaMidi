#include "rectangulo.h++"

Rectangulo::Rectangulo(Sombreador *sombreador) : Figura(sombreador)
{
	float puntos[16] = {
		//Posicion		Textura
		1.0f,	1.0f,	1.0f,	1.0f,	//Arriba Derecha
		1.0f,	0.0f,	1.0f,	0.0f,	//Abajo Derecha
		0.0f,	1.0f,	0.0f,	1.0f,	//Arriba Izquierda
		0.0f,	0.0f,	0.0f,	0.0f		//Abajo Izquierda
	};

	this->indice_figura = 0;//Matriz de vertice de objeto
	glGenVertexArrays(1, &this->indice_figura);
	glBindVertexArray(this->indice_figura);
	Figura::Ultimo_indice_seleccionado = this->indice_figura;

	m_indice_objeto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &m_indice_objeto);
	glBindBuffer(GL_ARRAY_BUFFER, m_indice_objeto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(puntos), puntos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_color_rectangulo = Color(1.0f, 1.0f, 1.0f);
	m_textura_activada = true;
	m_textura_estirable_horizontal = false;
	m_textura_estirable_vertical = false;

	sombreador->uniforme_vector4f("color", m_color_rectangulo.rojo(), m_color_rectangulo.verde(), m_color_rectangulo.azul(), 1.0f);
	sombreador->uniforme_bool("textura_activada", m_textura_activada);
	sombreador->uniforme_bool("textura_estirable_horizontal", m_textura_estirable_horizontal);
	sombreador->uniforme_bool("textura_estirable_vertical", m_textura_estirable_vertical);
}

Rectangulo::~Rectangulo()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &this->indice_figura);
	glDeleteBuffers(1, &m_indice_objeto);
}

void Rectangulo::color(Color color_nuevo)
{
	if(m_color_rectangulo != color_nuevo)
	{
		m_color_rectangulo = color_nuevo;
		sombreador->uniforme_vector4f("color", m_color_rectangulo.rojo(), m_color_rectangulo.verde(), m_color_rectangulo.azul(), m_color_rectangulo.alfa());
	}
}

void Rectangulo::textura(bool estado)
{
	if(m_textura_activada != estado)
	{
		m_textura_activada = estado;
		sombreador->uniforme_bool("textura_activada", m_textura_activada);
	}
}

void Rectangulo::extremos_fijos(bool horizontal, bool vertical)
{
	if(m_textura_estirable_horizontal != horizontal)
	{
		m_textura_estirable_horizontal = horizontal;
		sombreador->uniforme_bool("textura_estirable_horizontal", m_textura_estirable_horizontal);
	}

	if(m_textura_estirable_vertical != vertical)
	{
		m_textura_estirable_vertical = vertical;
		sombreador->uniforme_bool("textura_estirable_vertical", m_textura_estirable_vertical);
	}
}

void Rectangulo::dibujar(float x, float y, float ancho, float alto, Color color)
{
	this->color(color);
	this->dibujar(x, y, ancho, alto);
}

void Rectangulo::dibujar(float x, float y, float ancho, float alto)
{
	glm::mat4 modelo = glm::mat4(1.0f);
	modelo = glm::translate(modelo, glm::vec3(x, y, 0.0f));
	modelo = glm::scale(modelo, glm::vec3(ancho, alto, 1.0f));
	this->sombreador->uniforme_matriz4("modelo", modelo);

	if(Figura::Ultimo_indice_seleccionado != this->indice_figura)
	{
		glBindVertexArray(this->indice_figura);
		Figura::Ultimo_indice_seleccionado = this->indice_figura;
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Rectangulo::dibujar_estirable(float x, float y, float ancho, float alto, float borde_horizontal, float borde_vertical)
{
	//Dibuja un rectangulo con textura fija arriba y abajo de alto variable en el centro.
	bool cambio = false;

	if(borde_horizontal <= 0 && m_textura_estirable_horizontal)
	{
		m_textura_estirable_horizontal = false;
		sombreador->uniforme_bool("textura_estirable_horizontal", false);
		borde_horizontal = 0;
	}

	if(borde_vertical <= 0 && m_textura_estirable_vertical)
	{
		m_textura_estirable_vertical = false;
		sombreador->uniforme_bool("textura_estirable_vertical", false);
		borde_vertical = 0;
	}

	if(borde_horizontal > 0 && !m_textura_estirable_horizontal)
	{
		m_textura_estirable_horizontal = true;
		sombreador->uniforme_bool("textura_estirable_horizontal", true);
	}
	if(borde_vertical > 0 && !m_textura_estirable_vertical)
	{
		m_textura_estirable_vertical = true;
		sombreador->uniforme_bool("textura_estirable_vertical", true);
	}

	if(m_borde_horizontal != borde_horizontal / ancho)
	{
		m_borde_horizontal = borde_horizontal / ancho;
		cambio = true;
	}

	if(m_borde_vertical != borde_vertical / alto)
	{
		m_borde_vertical = borde_vertical / alto;
		cambio = true;
	}

	if(cambio)
		sombreador->uniforme_vector2f("borde", m_borde_horizontal, m_borde_vertical);

	this->dibujar(x, y, ancho, alto);
}

