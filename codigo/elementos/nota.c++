#include "nota.h++"

Nota::Nota()
{
	this->tiempo_final = 0;
	this->pista = 0;
}

Nota::Nota(int tiempo_final, int pista)
{
	this->tiempo_final = tiempo_final;
	this->pista = pista;
}

Nota::~Nota()
{
}

void Nota::e_tiempo_final(int valor)
{
	this->tiempo_final = valor;
}

void Nota::e_pista(int valor)
{
	this->pista = valor;
}

void Nota::e_tiempo_y_pista(int tiempo, int pista)
{
	this->tiempo_final = tiempo;
	this->pista = pista;
}

int Nota::o_tiempo_final()
{
	return this->tiempo_final;
}

int Nota::o_pista()
{
	return this->pista;
}
