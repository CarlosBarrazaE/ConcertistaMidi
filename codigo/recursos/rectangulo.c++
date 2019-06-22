#include "rectangulo.h++"

Rectangulo::Rectangulo(Sombreador *sombreador, Color color) : Figura(sombreador)
{
	this->color = color;
	this->tiene_textura = false;
	inicializar();
}

Rectangulo::Rectangulo(Sombreador *sombreador, Textura2D *textura) : Figura(sombreador)
{
	this->color = Color(1.0, 1.0, 1.0);
	this->textura = textura;
	this->tiene_textura = true;
	inicializar();
}

Rectangulo::Rectangulo(Sombreador *sombreador, Textura2D *textura, Color color) : Figura(sombreador)
{
	this->color = color;
	this->textura = textura;
	this->tiene_textura = true;
	inicializar();
}

Rectangulo::~Rectangulo()
{
}

void Rectangulo::inicializar()
{
	int tamanno = 0;
	float *puntos;

	if(this->tiene_textura)
	{
		puntos = new float[16] {//XYZ
			//Posicion		Textura
			1.0,	1.0,	1.0,	1.0,	//Arriba Derecha
			1.0,	0.0,	1.0,	0.0,	//Abajo Derecha
			0.0,	1.0,	0.0,	1.0,	//Arriba Izquierda
			0.0,	0.0,	0.0,	0.0		//Abajo Izquierda
		};
		tamanno = 16;
	}
	else
	{
		puntos = new float[8] {//XYZ
			//Posicion
			1.0,	1.0,	//Arriba Derecha
			1.0,	0.0,	//Abajo Derecha
			0.0,	1.0,	//Arriba Izquierda
			0.0,	0.0		//Abajo Izquierda
		};
		tamanno = 8;
	}

	this->indice_figura = 0;//Matriz de vertice de objeto
	glGenVertexArrays(1, &this->indice_figura);
	glBindVertexArray(this->indice_figura);
	Figura::ultimo_indice_seleccionado = this->indice_figura;

	unsigned int vto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &vto);
	glBindBuffer(GL_ARRAY_BUFFER, vto);
	glBufferData(GL_ARRAY_BUFFER, tamanno * sizeof(float), puntos, GL_STATIC_DRAW);

	if(this->tiene_textura)
	{
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	else
	{
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangulo::seleccionar_color(Color color)
{
	this->color = color;
	sombreador->e_vector4f("color", this->color.o_rojo(), this->color.o_verde(), this->color.o_azul(), 1.0f);
}

void Rectangulo::dibujar_rectangulo(float x, float y, float ancho, float alto, Color color)
{
	this->color = color;
	dibujar_rectangulo(x, y, ancho, alto);
}

void Rectangulo::dibujar_rectangulo(float x, float y, float ancho, float alto)
{
	sombreador->e_vector4f("color", this->color.o_rojo(), this->color.o_verde(), this->color.o_azul(), 1.0f);

	if(this->tiene_textura)
		textura->activar();

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
