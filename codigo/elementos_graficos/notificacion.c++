#include "notificacion.h++"

std::string Notificacion::Texto = "";
int Notificacion::tiempo = 0;
CodigoEstado Notificacion::estado = EstadoNinguno;

Notificacion::Notificacion(Administrador_Recursos *recursos) : Elemento(0, 0, 400, 40, true), m_mensaje(recursos)
{
	m_mensaje.tipografia(recursos->tipografia(LetraChica));
	m_mensaje.color(Color(1.0f, 1.0f, 1.0f));
	m_mensaje.posicion(0, 0);
 	m_mensaje.dimension(400, 40);
	m_mensaje.centrado(true);

	m_textura_fondo = recursos->textura(T_Nota);
	m_rectangulo = recursos->figura(F_Rectangulo);

	m_tiempo_restante = 0;
	m_estado_mensaje = EstadoNinguno;
}

Notificacion::~Notificacion()
{
}

void Notificacion::actualizar(unsigned int diferencia_tiempo)
{
	if(Notificacion::tiempo != 0)
	{
		m_tiempo_restante = Notificacion::tiempo*60;
		m_mensaje.texto(Notificacion::Texto);
		m_estado_mensaje = Notificacion::estado;
		Notificacion::tiempo = 0;
	}
	if(m_tiempo_restante > 0)
		m_tiempo_restante -= (diferencia_tiempo / 1000000000.0) * 60;
}

void Notificacion::dibujar()
{
	if(m_tiempo_restante > 0)
	{
		m_textura_fondo->activar();
		m_rectangulo->textura(true);
		m_rectangulo->extremos_fijos(true, true);

		if(m_estado_mensaje == EstadoError)
			m_rectangulo->color(Color(0.7f, 0.0f, 0.0f));
		else if(m_estado_mensaje == EstadoAviso)
			m_rectangulo->color(Color(0.9f, 0.5f, 0.0f));
		else if(m_estado_mensaje == EstadoNota)
			m_rectangulo->color(Color(0.0f, 0.598f, 0.0f));
		else if(m_estado_mensaje == EstadoDepurar)
			m_rectangulo->color(Color(0.145f, 0.707f, 1.0f));

		m_rectangulo->dibujar_estirable(this->x(), this->y(), this->ancho(), this->alto(), 15.0f, 12.0f);
		m_rectangulo->extremos_fijos(false, false);
		m_mensaje.dibujar();
	}
}

void Notificacion::evento_raton(Raton */*raton*/)
{

}

void Notificacion::posicion(int x, int y)
{
	this->_posicion(x, y);
	m_mensaje.posicion(this->x(), this->y());
}

void Notificacion::quitar_notificaciones()
{
	m_tiempo_restante = 0;
}

void Notificacion::Error(std::string texto, int tiempo)
{
	Notificacion::Texto = texto;
	Notificacion::tiempo = tiempo;
	Notificacion::estado = EstadoError;
	Registro::Error(texto);
}

void Notificacion::Aviso(std::string texto, int tiempo)
{
	Notificacion::Texto = texto;
	Notificacion::tiempo = tiempo;
	Notificacion::estado = EstadoAviso;
	Registro::Aviso(texto);
}

void Notificacion::Nota(std::string texto, int tiempo)
{
	Notificacion::Texto = texto;
	Notificacion::tiempo = tiempo;
	Notificacion::estado = EstadoNota;
	Registro::Nota(texto);
}

void Notificacion::Depurar(std::string texto, int tiempo)
{
	Notificacion::Texto = texto;
	Notificacion::tiempo = tiempo;
	Notificacion::estado = EstadoDepurar;
	Registro::Depurar(texto);
}
