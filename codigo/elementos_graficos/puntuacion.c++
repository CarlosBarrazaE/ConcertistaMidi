#include "puntuacion.h++"

Puntuacion::Puntuacion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto), m_texto_puntaje(recursos), m_texto_aciertos(recursos), m_texto_maxcombo(recursos), m_texto_errores(recursos)
{
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_ultimo_tiempo = 0;
	m_puntaje_total = 0;
	m_notas_totales = 0;
	m_notas_tocadas = 0;
	m_errores = 0;
	m_maximo_combo = 0;
	m_combos = 0;

	Color color_letra(1.0f, 1.0f, 1.0f);
	m_texto_puntaje.texto("Puntaje: 0");
	m_texto_puntaje.tipografia(recursos->tipografia(LetraMediana));
	m_texto_puntaje.posicion(this->x()+5, this->y()+5);//Margen para el texto
	m_texto_puntaje.color(color_letra);

	m_texto_aciertos.texto("Notas: 0/0");
	m_texto_aciertos.tipografia(recursos->tipografia(LetraMediana));
	m_texto_aciertos.posicion(this->x()+5, this->y()+25);//Margen para el texto
	m_texto_aciertos.color(color_letra);

	m_texto_maxcombo.texto("Maximo Combo: 0");
	m_texto_maxcombo.tipografia(recursos->tipografia(LetraMediana));
	m_texto_maxcombo.posicion(this->x()+5, this->y()+45);//Margen para el texto
	m_texto_maxcombo.color(color_letra);

	m_texto_errores.texto("Errores: 0");
	m_texto_errores.tipografia(recursos->tipografia(LetraMediana));
	m_texto_errores.posicion(this->x()+5, this->y()+65);//Margen para el texto
	m_texto_errores.color(color_letra);
}

Puntuacion::~Puntuacion()
{
}

void Puntuacion::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Puntuacion::dibujar()
{
	if(m_notas_totales > 0)
	{
		m_rectangulo->textura(false);
		m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(0.5f, 0.5f, 0.5f, 0.5f));
		m_texto_puntaje.dibujar();
		m_texto_aciertos.dibujar();
		m_texto_maxcombo.dibujar();
		m_texto_errores.dibujar();
	}
}

void Puntuacion::evento_raton(Raton */*raton*/)
{
}

void Puntuacion::nota_correcta(unsigned int cantidad, microseconds_t tiempo, double velocidad)
{
	m_ultimo_tiempo = tiempo;
	Puntos puntaje_nuevo;
	puntaje_nuevo.tiempo = tiempo;

	//En el modo aprender la velocidad no importa por lo que envia 0
	if(velocidad <= 0)
		velocidad = 1;
	if(m_combos > 0)
		puntaje_nuevo.puntaje = static_cast<int>(static_cast<float>(cantidad) * 100.0f * static_cast<float>(velocidad)) + static_cast<int>(m_combos);
	else
		puntaje_nuevo.puntaje = static_cast<int>(static_cast<float>(cantidad) * 100.0f * static_cast<float>(velocidad));
	m_notas_tocadas += cantidad;
	m_puntaje_total += puntaje_nuevo.puntaje;
	m_puntuacion.push_back(puntaje_nuevo);
	m_texto_puntaje.texto("Puntaje: " + std::to_string(m_puntaje_total));
	m_texto_aciertos.texto("Notas: " + std::to_string(m_notas_tocadas) + "/" + std::to_string(m_notas_totales));
}

void Puntuacion::notas_totales(unsigned int total_nota)
{
	m_notas_totales = total_nota;
	m_texto_aciertos.texto("Notas: " + std::to_string(m_notas_tocadas) + "/" + std::to_string(m_notas_totales));
}

void Puntuacion::cambiar_a(microseconds_t tiempo_nuevo)
{
	//Revierte el puntaje si se retrocede el tiempo
	long int posicion_eliminar = 0;
	bool eliminar = false;
	if(tiempo_nuevo < m_ultimo_tiempo)
	{
		for(unsigned long int x = 0; x<m_puntuacion.size(); x++)
		{
			if(m_puntuacion[x].tiempo >= tiempo_nuevo)
			{
				//Encontro el punto inicial desde donde eliminar
				if(!eliminar)
				{
					eliminar = true;
					posicion_eliminar = static_cast<long int>(x);
				}
				//Quita el puntaje que esta despues cuando de retrocede
				//Los errores se quedan
				m_puntaje_total -= m_puntuacion[x].puntaje;
				m_notas_tocadas--;
			}
			else
			{
				//Recalcula el numero de notas y el ultimo tiempo registrado
				m_ultimo_tiempo = m_puntuacion[x].tiempo;
			}
		}
		if(eliminar)
		{
			m_puntuacion.erase(m_puntuacion.begin() + posicion_eliminar, m_puntuacion.end());
			m_texto_puntaje.texto("Puntaje: " + std::to_string(m_puntaje_total));
			m_texto_aciertos.texto("Notas: " + std::to_string(m_notas_tocadas) + "/" + std::to_string(m_notas_totales));
		}
	}
}

void Puntuacion::sumar_error()
{
	m_puntaje_total--;
	m_errores++;
	m_texto_puntaje.texto("Puntaje: " + std::to_string(m_puntaje_total));
	m_texto_errores.texto("Errores: " + std::to_string(m_errores));
}

void Puntuacion::combo(unsigned int combo)
{
	m_combos += combo;
	if(m_combos > m_maximo_combo)
	{
		m_maximo_combo = m_combos;
		m_texto_maxcombo.texto("Maximo Combo: " + std::to_string(m_maximo_combo));
	}
}

unsigned int Puntuacion::combo()
{
	return m_combos;
}

void Puntuacion::reiniciar_combo()
{
	m_combos = 0;
}
