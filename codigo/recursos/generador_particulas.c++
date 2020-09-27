#include "generador_particulas.h++"
#include <iostream>
float Generador_Particulas::Ultima_escala = 0;
Color Generador_Particulas::Color_anterior = Color(0.0f, 0.0f, 0.0f);

Generador_Particulas::Generador_Particulas(Sombreador *sombreador, Textura2D *textura, unsigned int particulas_maximas, float escala) : Figura(sombreador)
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

	m_indice_objeto = 0; //Vertice temporal de objeto
	glGenBuffers(1, &m_indice_objeto);
	glBindBuffer(GL_ARRAY_BUFFER, m_indice_objeto);
	glBufferData(GL_ARRAY_BUFFER, sizeof(puntos), puntos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for(unsigned int i=0; i < m_particulas_maximas;  i++)
		m_particulas.push_back(Particula());

	m_primera_particula_activa = 0;
	m_ultima_particula_activa = 0;
	m_particulas_activas = 0;

	m_sombreador->activar();
	m_sombreador->uniforme_float("escala", escala);
	m_sombreador->uniforme_vector4f("color", 0.0f, 0.0f, 0.0f, 0.0f);
	Generador_Particulas::Color_anterior = Color(0.0f, 0.0f, 0.0f);
	m_escala = escala;
	Generador_Particulas::Ultima_escala = escala;
}

Generador_Particulas::~Generador_Particulas()
{
	this->seleccionar_figura();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void Generador_Particulas::escala(float escala)
{
	m_escala = escala;
	m_sombreador->uniforme_float("escala", escala);
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
	m_sombreador->activar();
	m_textura->activar();

	if(Generador_Particulas::Ultima_escala != m_escala)
	{
		Generador_Particulas::Ultima_escala = m_escala;
		m_sombreador->uniforme_float("escala", Generador_Particulas::Ultima_escala);
	}

	Particula *p;
	unsigned int dibujar_particulas = 0;
	for(int i = static_cast<int>(m_primera_particula_activa); dibujar_particulas < m_particulas_activas; i++)
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
				m_sombreador->uniforme_vector4f("color", p->color.rojo(), p->color.verde(), p->color.azul(), p->color.alfa());
			}
			m_sombreador->uniforme_vector2f("posicion", p->posicion_x, p->posicion_y);


			this->seleccionar_figura();
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			dibujar_particulas++;
		}
		else
		{
			m_particulas_activas--;

			if(m_primera_particula_activa == static_cast<unsigned int>(i))
				m_primera_particula_activa++;

			//Si es igual al maximo es que tiene que empezar de nuevo el ciclo
			if(m_primera_particula_activa == m_particulas_maximas)
				m_primera_particula_activa = 0;
		}

		if(static_cast<unsigned int>(i) == m_particulas.size()-1)//Recorre el arreglo de forma circular
			i = -1;

		if(static_cast<unsigned int>(dibujar_particulas) == m_particulas_activas)
		{
			if(i < 0)
				m_ultima_particula_activa = 0;
			else
				m_ultima_particula_activa = static_cast<unsigned int>(i);
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Generador_Particulas::agregar_particulas(float x, float y, unsigned int cantidad_particulas, Color color)
{
	float aleatorio, aleatorio2;
	Particula *particula;
	for(unsigned int n=0; n<cantidad_particulas && m_particulas_activas < m_particulas_maximas; n++)
	{
		aleatorio = static_cast<float>((rand() % 100) - 50) / 10.0f;
		aleatorio2 = static_cast<float>((rand() % 100) - 50) / 10.0f;
		particula = &m_particulas[this->particula_inactiva()];
		particula->posicion_x = x + aleatorio;
		particula->posicion_y = y;
		particula->color = color;
		particula->vida = 1;
		particula->velocidad_x = aleatorio*10;
		particula->velocidad_y = aleatorio2*10;

		m_particulas_activas++;
	}
}
