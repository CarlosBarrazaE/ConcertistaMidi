#include "barra_desplazamiento.h++"
#include "../registro.h++"
Barra_Desplazamiento::Barra_Desplazamiento(int x, int y, int ancho, int alto, int columna, int fila, int margen_columna, int margen_fila, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	this->columna = columna;
	this->fila = fila;
	this->margen_columna = margen_columna;
	this->margen_fila = margen_fila;
	this->ancho_actual = 0;
	this->alto_actual = 0;
	this->desplazamiento_x = 0;
	this->desplazamiento_y = 0;

	this->calcular_posicion = true;

	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
	this->barra = recursos->obtener_textura(T_Barra);
}

Barra_Desplazamiento::~Barra_Desplazamiento()
{
}

void Barra_Desplazamiento::agregar_elemento(Elemento *e)
{
	elementos.push_back(e);
}

void Barra_Desplazamiento::actualizar(unsigned int diferencia_tiempo)
{
	if(this->calcular_posicion)
		this->actualizar_dimension();
	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->actualizar(diferencia_tiempo);
	}
}

void Barra_Desplazamiento::dibujar()
{
	Elemento *e;
	for(int i=0; i<elementos.size(); i++)
	{
		e = elementos.at(i);
		if(e->posicion_y() + e->o_alto() > this->y && e->posicion_y() < this->y + this->alto &&
			e->posicion_x() + e->o_ancho() > this->x && e->posicion_x() < this->x + this->ancho)
		{
			e->dibujar();
		}
	}
	this->rectangulo->textura(false);
	this->rectangulo->color(Color(0.95f, 0.95f, 0.95f));
	this->rectangulo->dibujar(this->x, this->y, this->ancho, this->margen_fila);
	this->rectangulo->dibujar(this->x, this->y+this->alto-this->margen_fila, this->ancho, this->margen_fila);

	if(this->alto < this->alto_actual)
	{
		this->barra->activar();
		this->rectangulo->extremos_fijos(false, true);
		this->rectangulo->textura(true);
		this->rectangulo->color(Color(0.7f, 0.7f, 0.7f));
		double proporcion = (double)(this->alto-20) / (double)this->alto_actual;
		this->rectangulo->dibujar_estirable(this->x+this->ancho-10, this->y+10, 10, this->alto-20, 0, 10);
		this->rectangulo->color(Color(0.5f, 0.5f, 0.5f));
		this->rectangulo->dibujar_estirable(this->x+this->ancho-10, this->y+10-this->desplazamiento_y*proporcion, 10, this->alto * proporcion, 0, 10);
		this->rectangulo->extremos_fijos(false, false);
	}
}

void Barra_Desplazamiento::evento_raton(Raton *raton)
{
	int dy = raton->dy();
	int desplazamiento_nuevo_y = 0;
	if(dy != 0)
	{
		int desplazamiento_anterior_y = this->desplazamiento_y;
		if(this->alto < this->alto_actual)
		{
			this->desplazamiento_y += dy*20;
			if(this->desplazamiento_y > 0)
				this->desplazamiento_y = 0;
			else if(this->desplazamiento_y < this->alto - this->alto_actual)
				this->desplazamiento_y = this->alto - this->alto_actual;

			desplazamiento_nuevo_y = this->desplazamiento_y - desplazamiento_anterior_y;
		}
	}

	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->posicion_y(elementos[i]->posicion_y() + desplazamiento_nuevo_y);
		elementos[i]->evento_raton(raton);
	}
}

void Barra_Desplazamiento::c_dimension(int ancho, int alto)
{
	this->ancho = ancho;
	this->alto = alto;
	this->calcular_posicion = true;
}

void Barra_Desplazamiento::actualizar_dimension()
{
	int numero_columnas = this->ancho / (this->columna + this->margen_columna);
	this->ancho_actual = (numero_columnas * this->columna) + ((numero_columnas - 1) * this->margen_columna);
	int x_inicio = (this->ancho - this->ancho_actual) / 2 + this->x;
	int x_actual = x_inicio;
	int y_actual = this->y + this->margen_fila;
	int contador_columnas = 1;
	for(int i=0; i<elementos.size(); i++)
	{
		elementos[i]->posicion_x(x_actual);
		elementos[i]->posicion_y(y_actual);

		if(contador_columnas < numero_columnas)
		{
			x_actual += this->columna + this->margen_columna;
		}
		else
		{
			contador_columnas = 0;
			x_actual = x_inicio;
			if(i<elementos.size()-1)
				y_actual += this->fila + this->margen_fila;
		}
		contador_columnas++;
	}
	this->alto_actual = y_actual + this->fila + this->margen_fila - this->y;

	this->desplazamiento_y = 0;
	this->calcular_posicion = false;
}
