#include "barra_progreso.h++"

Barra_Progreso::Barra_Progreso(int x, int y, int ancho, int alto, microseconds_t tiempo_total, MidiEventMicrosecondList lineas, Administrador_Recursos *recursos)
{
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->tiempo_total = tiempo_total;
	this->tiempo_actual = 0;
	this->lineas = lineas;
	this->tiempo_nuevo = -1;
	this->sobre_barra = false;
	this->x_anterior = 0;
	this->duracion_total = Funciones::milisegundos_a_texto(tiempo_total);

	t_frente = recursos->obtener_textura(T_FrenteBarraProgreso);
	rectangulo = recursos->obtener_figura(F_Rectangulo);
	this->texto = recursos->obtener_tipografia(LetraMuyChica);
	this->largo_texto = this->texto->ancho_texto(this->duracion_total);

	color_fondo = new Color(0.8f, 0.8f, 0.8f);
	color_progreso = new Color(0.0f, 0.761f, 0.467f);
}

Barra_Progreso::~Barra_Progreso()
{
	delete color_fondo;
	delete color_progreso;
}

void Barra_Progreso::e_tiempo(microseconds_t tiempo_actual)
{
	if(tiempo_actual < 0)
		this->tiempo_actual = 0;
	else
		this->tiempo_actual = tiempo_actual;
}

void Barra_Progreso::e_ancho(int ancho)
{
	this->ancho = ancho;
}

int Barra_Progreso::o_alto()
{
	return this->alto;
}

int Barra_Progreso::o_ancho()
{
	return this->ancho;
}

microseconds_t Barra_Progreso::o_tiempo_seleccionado()
{
	return this->tiempo_nuevo;
}

void Barra_Progreso::actualizar(unsigned int diferencia_tiempo)
{
	this->progreso = ((double)this->tiempo_actual / (double)this->tiempo_total) * this->ancho;
	if(progreso > this->ancho)
		this->progreso = this->ancho;
	else if(progreso < 0)
		this->progreso = 0;
}

void Barra_Progreso::dibujar()
{
	rectangulo->textura(false);
	rectangulo->dibujar(this->x, this->y, this->progreso, this->alto, *this->color_progreso);
	rectangulo->dibujar(this->x+this->progreso, this->y, this->ancho - this->progreso, this->alto, *this->color_fondo);

	rectangulo->color(Color(0.5f, 0.5f, 0.5f));
	for(int i=0; i<this->lineas.size(); i++)
	{
		rectangulo->dibujar(((double)lineas[i] / (double)this->tiempo_total) * this->ancho, this->y, 1, this->alto);
	}

	rectangulo->color(Color(0.15f, 0.15f, 0.15f));
	rectangulo->dibujar(this->x, this->y, this->ancho, 1);
	rectangulo->dibujar(this->x, this->y+this->alto-1, this->ancho, 1);

	t_frente->activar();
	rectangulo->textura(true);
	rectangulo->dibujar(this->x, this->y, this->ancho, this->alto, Color(1.0f, 1.0f, 1.0f));

	this->texto->imprimir(this->x+4, this->y + this->alto-4, Funciones::milisegundos_a_texto(this->tiempo_actual), Color(0.0f, 0.0f, 0.0f));
	this->texto->imprimir(this->x+this->ancho - (4 + this->largo_texto), this->y + this->alto-4, this->duracion_total, Color(0.0f, 0.0f, 0.0f));
}

void Barra_Progreso::evento_raton(Raton *raton)
{
	if(raton->x() >= this->x && raton->x() <= this->x + this->ancho &&
		raton->y() >= this->y && raton->y() <= this->y + this->alto)
	{
		if(raton->activado(BotonIzquierdo) && this->sobre_barra)
		{
			if(this->x_anterior != raton->x())
			{
				this->x_anterior = raton->x();
				this->tiempo_nuevo = ((double)raton->x() / (double)this->ancho) * this->tiempo_total;
			}
			else
				this->tiempo_nuevo = -1;
		}
		else if(!raton->activado(BotonIzquierdo))
		{
			this->sobre_barra = true;
			this->tiempo_nuevo = -1;
		}
	}
	else
	{
		this->sobre_barra = false;
		this->tiempo_nuevo = -1;
	}
}
