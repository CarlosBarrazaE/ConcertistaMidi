#include "ruta_exploracion.h++"

Ruta_Exploracion::Ruta_Exploracion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto)
{
	m_recursos = recursos;
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_boton_atraz = new Boton(x, y, 30, 30, "<", recursos);
	m_boton_atraz->color_boton(Color(1.0f, 1.0f, 1.0f));

	m_boton_adelante = new Boton(x+30, y, 30, 30, ">", recursos);
	m_boton_adelante->color_boton(Color(1.0f, 1.0f, 1.0f));

	m_carpeta_anterior = false;
	m_cambiar_carpeta = false;
	m_posicion_carpeta = 0;

	m_ancho_anterior = this->ancho();
	m_largo_actual = 0;
	m_primer_boton_mostrar = 0;
}

Ruta_Exploracion::~Ruta_Exploracion()
{
	delete m_boton_atraz;
	delete m_boton_adelante;

	for(Boton *b : m_carpetas)
		delete b;
}

void Ruta_Exploracion::calcular_posicion()
{
	//Calcular las nuevas posiciones
	if(m_largo_actual > this->ancho() || !Funciones::comparar_float(m_ancho_anterior ,this->ancho(), 0.01f))
	{
		float largo_actual = 65;
		float ancho_siguiente = 0;
		unsigned long int mostrar_actual = 0;

		//Encuentra el numero de botones que alcanzan
		if(m_carpetas.size() > 0)
		{
			ancho_siguiente = m_carpetas[m_carpetas.size()-1]->ancho();
			mostrar_actual = m_carpetas.size()-1;
		}
		for(unsigned long int x = m_carpetas.size(); x > 0 && largo_actual+ancho_siguiente < this->ancho(); x--)
		{
			//x-1 es una posicion valida
			largo_actual += m_carpetas[x-1]->ancho();
			mostrar_actual = x-1;

			if(x-1 > 0)
				ancho_siguiente = m_carpetas[x-2]->ancho();
		}

		if(m_primer_boton_mostrar != mostrar_actual)
		{
			m_primer_boton_mostrar = mostrar_actual;
			float posicion_texto = 65;
			//Actualiza las posiciones
			for(unsigned long int x = m_primer_boton_mostrar; x < m_carpetas.size(); x++)
			{
				m_carpetas[x]->posicion(this->x() + posicion_texto, this->y());
				posicion_texto +=  m_carpetas[x]->ancho();
			}
			m_largo_actual = posicion_texto;
		}
		m_ancho_anterior = this->ancho();
	}
}

void Ruta_Exploracion::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Ruta_Exploracion::dibujar()
{
	m_boton_atraz->dibujar();
	m_boton_adelante->dibujar();

	for(unsigned long int x = m_primer_boton_mostrar; x < m_carpetas.size(); x++)
		m_carpetas[x]->dibujar();
}

void Ruta_Exploracion::evento_raton(Raton *raton)
{
	m_boton_atraz->evento_raton(raton);
	if(m_boton_atraz->esta_activado())
		m_carpeta_anterior = true;

	m_boton_adelante->evento_raton(raton);
	for(unsigned long int x = m_primer_boton_mostrar; x<m_carpetas.size(); x++)
	{
		m_carpetas[x]->evento_raton(raton);
		if(m_carpetas[x]->esta_activado())
		{
			m_cambiar_carpeta = true;
			m_posicion_carpeta = x;
		}
	}
}

void Ruta_Exploracion::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
	this->calcular_posicion();
}

void Ruta_Exploracion::ruta_carpeta(const std::string &ruta_inicio, const std::string &ruta_completa, const std::string nombre_carpeta_inicial)
{
	//Borrar lista de botones si existe
	m_carpeta_anterior = false;
	m_cambiar_carpeta = false;
	m_posicion_carpeta = 0;
	if(m_carpetas.size() > 0)
	{
		for(Boton *b : m_carpetas)
			delete b;
		m_carpetas.clear();
		m_rutas_botones.clear();
	}

	if(ruta_completa.find(ruta_inicio) != std::string::npos)
	{
		float posicion_texto = 65;
		//Es la raiz
		m_carpetas.push_back(new Boton(this->x() + posicion_texto, this->y(), 30, 30, "/", LetraChica, m_recursos));
		m_rutas_botones.push_back("");
		posicion_texto +=  m_carpetas[m_carpetas.size()-1]->ancho();

		if(ruta_completa != "-")
		{
			//nombre_carpeta_inicial es la primera carpeta abierta
			m_carpetas.push_back(new Boton(this->x() + posicion_texto, this->y(), 30, 30, nombre_carpeta_inicial, LetraChica, m_recursos));
			m_rutas_botones.push_back(ruta_inicio);
			posicion_texto +=  m_carpetas[m_carpetas.size()-1]->ancho();
		}

		if(ruta_inicio.size() < ruta_completa.size())
		{
			std::string ruta_dividir = ruta_completa.substr(ruta_inicio.size());
			std::vector<std::string> carpetas = Texto::dividir_texto(ruta_dividir, '/');

			std::string ruta_actual = ruta_inicio;
			//Agrega un '/' al final si no lo tiene
			if(ruta_actual[ruta_actual.length()-1] != '/')
				ruta_actual += "/";

			for(unsigned long int x=0; x<carpetas.size(); x++)
			{
				//Guarda la ruta del boton actual
				ruta_actual += carpetas[x] + "/";
				m_rutas_botones.push_back(ruta_actual);

				//Agrega el boton actual
				m_carpetas.push_back(new Boton(this->x()+posicion_texto, this->y(), 30, 30, carpetas[x], LetraChica, m_recursos));
				posicion_texto += m_carpetas[m_carpetas.size()-1]->ancho();
			}
		}
		m_largo_actual = posicion_texto;
		m_primer_boton_mostrar = 0;
		this->calcular_posicion();
	}
	if(ruta_completa == "-")
		m_boton_atraz->habilitado(false);
	else
		m_boton_atraz->habilitado(true);
}

void Ruta_Exploracion::ir_atraz()
{
	m_carpeta_anterior = true;
}

bool Ruta_Exploracion::cambiar_carpeta()
{
	return m_carpeta_anterior || m_cambiar_carpeta;
}

bool Ruta_Exploracion::boton_siguiente()
{
	return m_boton_adelante->esta_activado();
}

void Ruta_Exploracion::boton_siguiente_habilitado(bool estado)
{
	m_boton_adelante->habilitado(estado);
}

std::string Ruta_Exploracion::nueva_ruta()
{
	if(m_carpeta_anterior && m_rutas_botones.size() > 1)
		return m_rutas_botones[m_rutas_botones.size()-2];

	if(m_cambiar_carpeta)
		return m_rutas_botones[m_posicion_carpeta];

	return "";
}
