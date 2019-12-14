#include "datos_musica.h++"

Datos_Musica::Datos_Musica()
{
	m_musica = NULL;
	m_nombre_musica = "Sin Titulo";
	m_autor = "Desconocido";
}

Datos_Musica::~Datos_Musica()
{
}

void Datos_Musica::cargar_midi(std::string direccion)
{
	m_musica = new Midi(Midi::ReadFromFile(direccion));
	this->reiniciar();
}

void Datos_Musica::e_pistas(std::vector<Pista> pistas)
{
	m_pistas = pistas;
}

void Datos_Musica::e_nombre_musica(std::string nombre)
{
	m_nombre_musica = nombre;
}

void Datos_Musica::e_autor(std::string autor)
{
	m_autor = autor;
}

void Datos_Musica::reiniciar()
{
	if(m_musica != NULL)
		m_musica->Reset(5500000, 1000000);
}

Midi *Datos_Musica::o_musica()
{
	return m_musica;
}

std::vector<Pista> *Datos_Musica::o_pistas()
{
	return &m_pistas;
}

std::string Datos_Musica::o_nombre_musica()
{
	return m_nombre_musica;
}

std::string Datos_Musica::o_autor()
{
	return m_autor;
}
