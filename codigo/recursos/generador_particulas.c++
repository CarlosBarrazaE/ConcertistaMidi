#include "generador_particulas.h++"
#include <iostream>
int Generador_Particulas::Ultima_escala = 0;
Color Generador_Particulas::Color_anterior = Color(0.0f, 0.0f, 0.0f);

Generador_Particulas::Generador_Particulas(Sombreador *sombreador, Textura2D *textura, unsigned int particulas_maximas, int escala) : Figura(sombreador)
{
	m_textura = textura;
	m_particulas_maximas = particulas_maximas;

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

	for(int i=0; i < m_particulas_maximas;  i++)
		m_particulas.push_back(Particula());

	m_primera_particula_activa = 0;
	m_ultima_particula_activa = 0;
	m_particulas_activas = 0;

	this->sombreador->activar();
	this->sombreador->uniforme_float("escala", escala);
	this->sombreador->uniforme_vector4f("color", 0.0f, 0.0f, 0.0f, 0.0f);
	Generador_Particulas::Color_anterior = Color(0.0f, 0.0f, 0.0f);
	m_escala = escala;
	Generador_Particulas::Ultima_escala = escala;
}

Generador_Particulas::~Generador_Particulas()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteVertexArrays(1, &this->indice_figura);
	glDeleteBuffers(1, &m_indice_objeto);
}

int Generador_Particulas::particula_inactiva()
{
	int particula = 0;
	if(m_particulas_activas < m_particulas_maximas)
	{
		particula = m_ultima_particula_activa;
		m_ultima_particula_activa++;

		//Si esta en el final comienza de nuevo, permite sobreescribir una particula que aun esta activa
		if(m_ultima_particula_activa == m_particulas_maximas)
			m_ultima_particula_activa = 0;
		return particula;
	}
	return 0;
}

void Generador_Particulas::escala(int escala)
{
	m_escala = escala;
	this->sombreador->uniforme_float("escala", escala);
}

void Generador_Particulas::actualizar(float tiempo)
{
	m_tiempo = tiempo;
}

void Generador_Particulas::dibujar()
{
	//Se sale si no hay particulas activas
	if(m_particulas_activas <= 0)
		return;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->sombreador->activar();
	m_textura->activar();

	if(Generador_Particulas::Ultima_escala != m_escala)
	{
		Generador_Particulas::Ultima_escala = m_escala;
		this->sombreador->uniforme_int("escala", Generador_Particulas::Ultima_escala);
	}

	Particula *p;
	int dibujar_particulas = 0;
	for(int i = m_primera_particula_activa; dibujar_particulas < m_particulas_activas; i++)
	{
		p = &m_particulas[i];
		p->vida -= m_tiempo;

		if(p->vida > 0.0)
		{
			p->posicion_x -= p->velocidad_x*m_tiempo;
			p->posicion_y -= p->velocidad_y*m_tiempo;
			p->color.alfa(-m_tiempo);

			if(Generador_Particulas::Color_anterior != p->color)
			{
				Generador_Particulas::Color_anterior = p->color;
				this->sombreador->uniforme_vector4f("color", p->color.rojo(), p->color.verde(), p->color.azul(), p->color.alfa());
			}
			this->sombreador->uniforme_vector2f("posicion", p->posicion_x, p->posicion_y);


			if(Figura::Ultimo_indice_seleccionado != this->indice_figura)
			{
				glBindVertexArray(this->indice_figura);
				Figura::Ultimo_indice_seleccionado = this->indice_figura;
			}
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			dibujar_particulas++;
		}
		else
		{
			m_particulas_activas--;

			if(m_primera_particula_activa == i)
				m_primera_particula_activa++;

			//Si es igual al maximo es que tiene que empezar de nuevo el ciclo
			if(m_primera_particula_activa == m_particulas_maximas)
				m_primera_particula_activa = 0;
		}

		if(i == m_particulas.size()-1)//Recorre el arreglo de forma circular
			i = -1;

		if(dibujar_particulas == m_particulas_activas)
		{
			if(i < 0)
				m_ultima_particula_activa = 0;
			else
				m_ultima_particula_activa = i;
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Generador_Particulas::agregar_particulas(int x, int y, unsigned int cantidad_particulas, Color color)
{
	float aleatorio, aleatorio2;
	Particula *particula;
	for(int n=0; n<cantidad_particulas && m_particulas_activas < m_particulas_maximas; n++)
	{
		aleatorio = ((rand() % 100) - 50) / 10.0;
		aleatorio2 = ((rand() % 100) - 50) / 10.0;
		particula = &m_particulas[this->particula_inactiva()];
		particula->posicion_x = x + aleatorio;
		particula->posicion_y = y;
		particula->color = color;
		particula->vida = 1.0;
		particula->velocidad_x = aleatorio*10;
		particula->velocidad_y = aleatorio2*10;

		m_particulas_activas++;
	}
}
