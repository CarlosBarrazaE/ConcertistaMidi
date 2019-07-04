#include "rectangulo.h++"

Rectangulo::Rectangulo(Sombreador *sombreador) : Figura(sombreador)
{
	int tamanno = 0;
	float puntos[16] = {
		//Posicion		Textura
		1.0,	1.0,	1.0,	1.0,	//Arriba Derecha
		1.0,	0.0,	1.0,	0.0,	//Abajo Derecha
		0.0,	1.0,	0.0,	1.0,	//Arriba Izquierda
		0.0,	0.0,	0.0,	0.0		//Abajo Izquierda
	};

	this->indice_figura = 0;//Matriz de vertice de objeto
	glGenVertexArrays(1, &this->indice_figura);
	glBindVertexArray(this->indice_figura);
	Figura::ultimo_indice_seleccionado = this->indice_figura;

	unsigned int vto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &vto);
	glBindBuffer(GL_ARRAY_BUFFER, vto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(puntos), puntos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->color_rectangulo = Color(1.0, 1.0, 1.0);
	this->textura_activada = true;

	sombreador->e_vector4f("color", this->color_rectangulo.o_rojo(), this->color_rectangulo.o_verde(), this->color_rectangulo.o_azul(), 1.0f);
	sombreador->e_bool("textura_activada", this->textura_activada);
}

Rectangulo::~Rectangulo()
{
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

void Rectangulo::dibujar(float x, float y, float ancho, float alto, Color color, bool textura)
{
	this->textura(textura);
	this->color(color);
	this->dibujar(x, y, ancho, alto);
}

void Rectangulo::dibujar(float x, float y, float ancho, float alto, Color color)
{
	this->color(color);
	this->dibujar(x, y, ancho, alto);
}

void Rectangulo::dibujar(float x, float y, float ancho, float alto)
{
	glm::mat4 modelo = glm::mat4(1.0);
	modelo = glm::translate(modelo, glm::vec3(x, y, 0.0));
	modelo = glm::scale(modelo, glm::vec3(ancho, alto, 1.0));
	this->sombreador->e_matriz4("modelo", modelo);

	if(Figura::ultimo_indice_seleccionado != this->indice_figura)
	{
		glBindVertexArray(this->indice_figura);
		Figura::ultimo_indice_seleccionado = this->indice_figura;
	}
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
