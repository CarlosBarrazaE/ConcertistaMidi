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
}

Ruta_Exploracion::~Ruta_Exploracion()
{
	delete m_boton_atraz;
	delete m_boton_adelante;

	for(Boton *b : m_carpetas)
		delete b;
}

void Ruta_Exploracion::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Ruta_Exploracion::dibujar()
{
	m_rectangulo->textura(false);

	m_boton_atraz->dibujar();
	m_boton_adelante->dibujar();

	for(Boton *b : m_carpetas)
		b->dibujar();
}

void Ruta_Exploracion::evento_raton(Raton *raton)
{
	m_boton_atraz->evento_raton(raton);
	if(m_boton_atraz->esta_activado())
		m_carpeta_anterior = true;

	m_boton_adelante->evento_raton(raton);
	for(unsigned long int x = 0; x<m_carpetas.size(); x++)
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
			std::vector<std::string> carpetas = Funciones::dividir_texto(ruta_dividir, '/');

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
	}
	if(ruta_completa == "-")
		m_boton_atraz->habilitado(false);
	else
		m_boton_atraz->habilitado(true);
}

bool Ruta_Exploracion::cambiar_carpeta()
{
	return m_carpeta_anterior || m_cambiar_carpeta;
}

bool Ruta_Exploracion::boton_siguiente()
{
	return m_boton_adelante->esta_activado();
}

std::string Ruta_Exploracion::nueva_ruta()
{
	if(m_carpeta_anterior && m_rutas_botones.size() > 1)
		return m_rutas_botones[m_rutas_botones.size()-2];

	if(m_cambiar_carpeta)
		return m_rutas_botones[m_posicion_carpeta];

	return "";
}
