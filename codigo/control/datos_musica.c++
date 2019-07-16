#include "datos_musica.h++"

Datos_Musica::Datos_Musica()
{
	this->musica = NULL;
	this->nombre_musica = "Sin Titulo";
	this->autor = "Desconocido";
}

Datos_Musica::~Datos_Musica()
{
}

void Datos_Musica::cargar_midi(std::string direccion)
{
	this->musica = new Midi(Midi::ReadFromFile(direccion));
	this->reiniciar();
}

void Datos_Musica::e_pistas(std::vector<Pista> pistas)
{
	this->pistas = pistas;
}

void Datos_Musica::e_nombre_musica(std::string nombre)
{
	this->nombre_musica = nombre;
}

void Datos_Musica::e_autor(std::string autor)
{
	this->autor = autor;
}

void Datos_Musica::reiniciar()
{
	if(this->musica != NULL)
		this->musica->Reset(5500000, 1000000);
}

Midi *Datos_Musica::o_musica()
{
	return this->musica;
}

std::vector<Pista> *Datos_Musica::o_pistas()
{
	return &this->pistas;
}

std::string Datos_Musica::o_nombre_musica()
{
	return this->nombre_musica;
}

std::string Datos_Musica::o_autor()
{
	return this->autor;
}
