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

	this->indice_objeto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &this->indice_objeto);
	glBindBuffer(GL_ARRAY_BUFFER, this->indice_objeto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(puntos), puntos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->color_rectangulo = Color(1.0, 1.0, 1.0);
	this->textura_activada = true;
	this->textura_estirable = false;

	sombreador->e_vector4f("color", this->color_rectangulo.o_rojo(), this->color_rectangulo.o_verde(), this->color_rectangulo.o_azul(), 1.0f);
	sombreador->e_bool("textura_activada", this->textura_activada);
	sombreador->e_bool("textura_estirable", this->textura_estirable);
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

void Rectangulo::extremos_fijos(bool estado)
{
	if(this->textura_estirable != estado)
	{
		this->textura_estirable = estado;
		sombreador->e_bool("textura_estirable", this->textura_estirable);
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

void Rectangulo::dibujar_estirable(float x, float y, float ancho, float alto, float borde_vertical)
{
	//Dibuja un rectangulo con textura fija arriba y abajo de alto variable en el centro.

	//Requiere activar el uso de textura_estirable y establecer un valor mayor que 0 para el borde
	if(!this->textura_estirable || borde_vertical <= 0)//Si no cumple las condiciones se dibuja un rectangulo normal
		this->dibujar(x, y, ancho, alto);
	else
	{
		int alto_nuevo = borde_vertical*2;//Es el tamaño minimo para la nota
		if(alto_nuevo < alto)
			alto_nuevo = alto;

		if(this->borde_vertical != borde_vertical / alto_nuevo)
		{
			this->borde_vertical = borde_vertical / alto_nuevo;
			sombreador->e_float("borde", this->borde_vertical);
		}

		//x, y es el punto base comenzando de abajo hacia arriba
		this->dibujar(x, y-alto_nuevo, ancho, alto_nuevo);
	}
}

