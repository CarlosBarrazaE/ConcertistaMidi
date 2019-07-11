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
	Figura::ultimo_indice_seleccionado = this->indice_figura;

	this->indice_objeto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &this->indice_objeto);
	glBindBuffer(GL_ARRAY_BUFFER, this->indice_objeto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(puntos), puntos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->color_rectangulo = Color(1.0f, 1.0f, 1.0f);
	this->textura_activada = true;
	this->textura_estirable_horizontal = false;
	this->textura_estirable_vertical = false;

	sombreador->e_vector4f("color", this->color_rectangulo.o_rojo(), this->color_rectangulo.o_verde(), this->color_rectangulo.o_azul(), 1.0f);
	sombreador->e_bool("textura_activada", this->textura_activada);
	sombreador->e_bool("textura_estirable_horizontal", this->textura_estirable_horizontal);
	sombreador->e_bool("textura_estirable_vertical", this->textura_estirable_vertical);
}

Rectangulo::~Rectangulo()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &this->indice_figura);
	glDeleteBuffers(1, &this->indice_objeto);
}

void Rectangulo::color(Color color_nuevo)
{
	if(this->color_rectangulo != color_nuevo)
	{
		this->color_rectangulo = color_nuevo;
		sombreador->e_vector4f("color", this->color_rectangulo.o_rojo(), this->color_rectangulo.o_verde(), this->color_rectangulo.o_azul(), 1.0f);
	}
}

void Rectangulo::textura(bool estado)
{
	if(this->textura_activada != estado)
	{
		this->textura_activada = estado;
		sombreador->e_bool("textura_activada", this->textura_activada);
	}
}

void Rectangulo::extremos_fijos(bool horizontal, bool vertical)
{
	if(this->textura_estirable_horizontal != horizontal)
	{
		this->textura_estirable_horizontal = horizontal;
		sombreador->e_bool("textura_estirable_horizontal", this->textura_estirable_horizontal);
	}

	if(this->textura_estirable_vertical != vertical)
	{
		this->textura_estirable_vertical = vertical;
		sombreador->e_bool("textura_estirable_vertical", this->textura_estirable_vertical);
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
	this->sombreador->e_matriz4("modelo", modelo);

	if(Figura::ultimo_indice_seleccionado != this->indice_figura)
	{
		glBindVertexArray(this->indice_figura);
		Figura::ultimo_indice_seleccionado = this->indice_figura;
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Rectangulo::dibujar_estirable(float x, float y, float ancho, float alto, float borde_horizontal, float borde_vertical)
{
	//Dibuja un rectangulo con textura fija arriba y abajo de alto variable en el centro.
	bool cambio = false;

	if(borde_horizontal <= 0 && this->textura_estirable_horizontal)
	{
		this->textura_estirable_horizontal = false;
		sombreador->e_bool("textura_estirable_horizontal", false);
		borde_horizontal = 0;
	}

	if(borde_vertical <= 0 && this->textura_estirable_vertical)
	{
		this->textura_estirable_vertical = false;
		sombreador->e_bool("textura_estirable_vertical", false);
		borde_vertical = 0;
	}

	if(borde_horizontal > 0 && !this->textura_estirable_horizontal)
	{
		this->textura_estirable_horizontal = true;
		sombreador->e_bool("textura_estirable_horizontal", true);
	}
	if(borde_vertical > 0 && !this->textura_estirable_vertical)
	{
		this->textura_estirable_vertical = true;
		sombreador->e_bool("textura_estirable_vertical", true);
	}

	if(this->borde_horizontal != borde_horizontal / ancho)
	{
		this->borde_horizontal = borde_horizontal / ancho;
		cambio = true;
	}

	if(this->borde_vertical != borde_vertical / alto)
	{
		this->borde_vertical = borde_vertical / alto;
		cambio = true;
	}

	if(cambio)
		sombreador->e_vector2f("borde", this->borde_horizontal, this->borde_vertical);

	this->dibujar(x, y, ancho, alto);
}

