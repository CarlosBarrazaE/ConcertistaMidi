#include "teclado.h++"

Teclado::Teclado()
{
	//Teclado predeterminado de 88 teclas
	this->numero_blancas = 52;
	this->numero_negras = 36;
	this->inicio_blanca = 1;
	this->inicio_negra = 4;
	this->desplazamiento_blancas = 0;
	this->desplazamiento_negras = 0;
	this->primera_barra = 2;
	this->en_do_primera_barra = true;
}

Teclado::Teclado(int numero_b,int numero_n, int inicio_b, int inicio_n, int desplazamiento_b, int desplazamiento_n, int primera_barra, bool en_do_primera_barra)
{
	this->numero_blancas = numero_b;
	this->numero_negras = numero_n;
	this->inicio_blanca = inicio_b;
	this->inicio_negra = inicio_n;
	this->desplazamiento_blancas = desplazamiento_b;
	this->desplazamiento_negras = desplazamiento_n;
	this->primera_barra = primera_barra;
	this->en_do_primera_barra = en_do_primera_barra;
}

int Teclado::o_numero_blancas()
{
	return this->numero_blancas;
}

int Teclado::o_numero_negras()
{
	return this->numero_negras;
}

int Teclado::o_inicio_blancas()
{
	return this->inicio_blanca;
}

int Teclado::o_inicio_negras()
{
	return this->inicio_negra;
}

int Teclado::o_desplazamiento_blancas()
{
	return this->desplazamiento_blancas;
}

int Teclado::o_desplazamiento_negras()
{
	return this->desplazamiento_negras;
}

int Teclado::o_primera_barra()
{
	return this->primera_barra;
}

bool Teclado::o_en_do_primera_barra()
{
	return this->en_do_primera_barra;
}
