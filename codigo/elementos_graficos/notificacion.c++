#include "notificacion.h++"

std::vector<Mensaje *> Notificacion::notificaciones;

Notificacion::Notificacion(Administrador_Recursos *recursos) : Elemento(0, 0, 400, 40, true)
{
	m_recursos = recursos;
	m_textura_fondo = recursos->textura(T_Nota);
	m_rectangulo = recursos->figura(F_Rectangulo);
}

Notificacion::~Notificacion()
{
	for(Mensaje *m : Notificacion::notificaciones)
		delete m;
}

void Notificacion::actualizar(unsigned int diferencia_tiempo)
{
	//Maximo 7 notificaciones a la vez
	unsigned int contador = 0;
	for(unsigned int x=0; x<Notificacion::notificaciones.size() && contador < MAXIMAS_NOTIFICACIONES; x++)
	{
		if(Notificacion::notificaciones[x]->etiqueta == NULL)
		{
			Notificacion::notificaciones[x]->etiqueta = new Etiqueta(0, 0, 400, 40, true, Notificacion::notificaciones[x]->texto, LetraChica, m_recursos);
			Notificacion::notificaciones[x]->etiqueta->centrado_vertical(true);
			Notificacion::notificaciones[x]->etiqueta->color(Color(1.0f, 1.0f, 1.0f));
		}
		else if(Notificacion::notificaciones[x]->tiempo > 0)
		{
			Notificacion::notificaciones[x]->tiempo -= (diferencia_tiempo / 1000000000.0) * 60;
			if(Notificacion::notificaciones[x]->tiempo <= 0)
			{
				//Eliminar esta notificacion
				delete Notificacion::notificaciones.at(x);
				Notificacion::notificaciones.erase(Notificacion::notificaciones.begin()+x);
				x--;
			}
			else
				contador++;
		}
	}
}

void Notificacion::dibujar()
{
	if(Notificacion::notificaciones.size() == 0)
		return;

	int posicion_y = 0;

	m_rectangulo->textura(true);
	m_rectangulo->extremos_fijos(true, true);
	for(unsigned int x=0; x<Notificacion::notificaciones.size() && x < MAXIMAS_NOTIFICACIONES; x++)
	{
		if(Notificacion::notificaciones[x]->estado == EstadoError)
			m_rectangulo->color(Color(0.7f, 0.0f, 0.0f));
		else if(Notificacion::notificaciones[x]->estado == EstadoAviso)
			m_rectangulo->color(Color(0.9f, 0.5f, 0.0f));
		else if(Notificacion::notificaciones[x]->estado == EstadoNota)
			m_rectangulo->color(Color(0.0f, 0.598f, 0.0f));
		else if(Notificacion::notificaciones[x]->estado == EstadoDepurar)
			m_rectangulo->color(Color(0.145f, 0.707f, 1.0f));

		m_textura_fondo->activar();
		m_rectangulo->dibujar_estirable(this->x(), this->y() + posicion_y, this->ancho(), this->alto(), 15.0f, 12.0f);
		m_rectangulo->extremos_fijos(false, false);
		Notificacion::notificaciones[x]->etiqueta->posicion(this->x(), this->y() + posicion_y);
		Notificacion::notificaciones[x]->etiqueta->dibujar();
		posicion_y += 45;
	}
}

void Notificacion::evento_raton(Raton */*raton*/)
{

}

void Notificacion::posicion(int x, int y)
{
	this->_posicion(x, y);
}

void Notificacion::Registrar(std::string texto, int tiempo, CodigoEstado estado)
{
	Notificacion::notificaciones.push_back(new Mensaje(NULL, texto, tiempo*60, estado));
}

void Notificacion::Error(std::string texto, int tiempo)
{
	Notificacion::Registrar(texto, tiempo, EstadoError);
	Registro::Error(texto);
}

void Notificacion::Aviso(std::string texto, int tiempo)
{
	Notificacion::Registrar(texto, tiempo, EstadoAviso);
	Registro::Aviso(texto);
}

void Notificacion::Nota(std::string texto, int tiempo)
{
	Notificacion::Registrar(texto, tiempo, EstadoNota);
	Registro::Nota(texto);
}

void Notificacion::Depurar(std::string texto, int tiempo)
{
	Notificacion::Registrar(texto, tiempo, EstadoDepurar);
	Registro::Depurar(texto);
}
