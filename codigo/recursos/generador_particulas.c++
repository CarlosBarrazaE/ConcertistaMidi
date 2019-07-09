#include "generador_particulas.h++"
#include <iostream>
int Generador_Particulas::ultima_escala = 0;
Color Generador_Particulas::color_anterior = Color(0.0f, 0.0f, 0.0f);

Generador_Particulas::Generador_Particulas(Sombreador *sombreador, Textura2D *textura, unsigned int particulas_maximas, int escala) : Figura(sombreador)
{
	this->textura = textura;
	this->particulas_maximas = particulas_maximas;

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

	for(int i=0; i < this->particulas_maximas;  i++)
		this->particulas.push_back(Particula());

	this->primera_particula_activa = 0;
	this->ultima_particula_activa = 0;
	this->particulas_activas = 0;

	this->sombreador->activar();
	this->sombreador->e_int("escala", escala);
	this->sombreador->e_vector4f("color", 0.0f, 0.0f, 0.0f, 0.0f);
	Generador_Particulas::color_anterior = Color(0.0f, 0.0f, 0.0f);
	this->escala = escala;
	Generador_Particulas::ultima_escala = escala;
}

Generador_Particulas::~Generador_Particulas()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &this->indice_figura);
	glDeleteBuffers(1, &this->indice_objeto);
}

int Generador_Particulas::obtener_particula_inactiva()
{
	int particula = 0;
	if(this->particulas_activas < this->particulas_maximas)
	{
		particula = this->ultima_particula_activa;
		this->ultima_particula_activa++;

		//Si esta en el final comienza de nuevo, permite sobreescribir una particula que aun esta activa
		if(this->ultima_particula_activa == this->particulas_maximas)
			this->ultima_particula_activa = 0;
		return particula;
	}
	return 0;
}

void Generador_Particulas::e_escala(int escala)
{
	this->escala = escala;
}

void Generador_Particulas::actualizar(float tiempo)
{
	this->tiempo = tiempo;
}

void Generador_Particulas::dibujar()
{
	//Se sale si no hay particulas activas
	if(this->particulas_activas <= 0)
		return;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->sombreador->activar();
	this->textura->activar();

	if(Generador_Particulas::ultima_escala != this->escala)
	{
		Generador_Particulas::ultima_escala = this->escala;
		this->sombreador->e_int("escala", Generador_Particulas::ultima_escala);
	}

	Particula *p;
	int dibujar_particulas = 0;
	for(int i=this->primera_particula_activa; dibujar_particulas<this->particulas_activas; i++)
	{
		p = &this->particulas[i];
		p->vida -= this->tiempo;

		if(p->vida > 0.0)
		{
			p->posicion_x -= p->velocidad_x*this->tiempo;
			p->posicion_y -= p->velocidad_y*this->tiempo;
			p->color.c_alfa(-this->tiempo);

			if(Generador_Particulas::color_anterior != p->color)
			{
				Generador_Particulas::color_anterior = p->color;
				this->sombreador->e_vector4f("color", p->color.o_rojo(), p->color.o_verde(), p->color.o_azul(), p->color.o_alfa());
			}
			this->sombreador->e_vector2f("posicion", p->posicion_x, p->posicion_y);


			if(Figura::ultimo_indice_seleccionado != this->indice_figura)
			{
				glBindVertexArray(this->indice_figura);
				Figura::ultimo_indice_seleccionado = this->indice_figura;
			}
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			dibujar_particulas++;
		}
		else
		{
			this->particulas_activas--;

			if(this->primera_particula_activa == i)
				this->primera_particula_activa++;

			//Si es igual al maximo es que tiene que empezar de nuevo el ciclo
			if(this->primera_particula_activa == this->particulas_maximas)
				this->primera_particula_activa = 0;
		}

		if(i == this->particulas.size()-1)//Recorre el arreglo de forma circular
			i = -1;

		if(dibujar_particulas == this->particulas_activas)
		{
			if(i < 0)
				this->ultima_particula_activa = 0;
			else
				this->ultima_particula_activa = i;
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Generador_Particulas::agregar_particulas(int x, int y, unsigned int cantidad_particulas, Color color)
{
	float aleatorio, aleatorio2;
	Particula *particula;
	for(int n=0; n<cantidad_particulas && this->particulas_activas < this->particulas_maximas; n++)
	{
		aleatorio = ((rand() % 100) - 50) / 10.0;
		aleatorio2 = ((rand() % 100) - 50) / 10.0;
		particula = &particulas[this->obtener_particula_inactiva()];
		particula->posicion_x = x + aleatorio;
		particula->posicion_y = y;
		particula->color = color;
		particula->vida = 1.0;
		particula->velocidad_x = aleatorio*10;
		particula->velocidad_y = aleatorio2*10;

		this->particulas_activas++;
	}
}
