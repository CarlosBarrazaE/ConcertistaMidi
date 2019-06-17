#include "boton.h++"

Boton::Boton(int x, int y, int ancho, int alto, std::string texto, Textura2D *textura, Color color, bool centrado, Administrador_Recursos *recursos) : Elemento()
{
	if(centrado)
		this->x = x - ancho / 2.0;
	else
		this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->texto_boton = texto;
	this->textura_boton = textura;
	this->centrado = centrado;
	this->sobre_boton = false;
	this->boton_pre_activado = false;
	this->boton_activado = false;

	color_boton_normal = color;
	color_boton_sobre.e_color(1.0, 1.0, 0.2);
	color_boton_activo.e_color(0.2, 1.0, 1.0);
	color_texto.e_color(0.2, 0.2, 0.2);

	color_boton = color_boton_normal;

	imprimir = recursos->obtener_tipografia(LetraMediana);
	sombreador = recursos->obtener_sombreador(Rectangulo_Textura);
	fondo = new Rectangulo(sombreador, textura_boton, color_boton);
}

Boton::~Boton()
{
	delete fondo;
}

void Boton::posicion_x(int x)
{
	if(centrado)
		this->x = x - ancho / 2.0;
	else
		this->x = x;
}

void Boton::posicion_y(int y)
{
	this->y = y;
}

void Boton::actualizar(Raton *raton)
{
	if(raton->x() >= this->x && raton->x() <= this->x + this->ancho &&
		raton->y() >= this->y && raton->y() <= this->y + this->alto)
	{
		if(raton->activado(BotonIzquierdo) && this->sobre_boton)
		{
			color_boton = color_boton_sobre;
			this->boton_pre_activado = true;
		}
		else if(!raton->activado(BotonIzquierdo))
		{
			color_boton = color_boton_activo;
			this->sobre_boton = true;
			if(this->boton_pre_activado)
				this->boton_activado = true;
		}
	}
	else
	{
		color_boton = color_boton_normal;
		this->sobre_boton = false;
		this->boton_pre_activado = false;
		this->boton_activado = false;
	}
}

void Boton::dibujar()
{
	fondo->dibujar_rectangulo(this->x, this->y, this->ancho, this->alto, color_boton);
	imprimir->dibujar_texto(this->x+this->ancho / 2.0, this->y+this->alto/2.0 + 7, this->texto_boton, color_texto, true);
}

bool Boton::esta_activado()
{
	return this->boton_activado;
}
