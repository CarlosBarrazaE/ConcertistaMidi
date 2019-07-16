#ifndef DATOS_MUSICA_H
#define DATOS_MUSICA_H

#include <vector>
#include "../control/pista.h++"
#include "../libmidi/Midi.h++"

class Datos_Musica
{
private:
	Midi *musica;
	std::vector<Pista> pistas;

	std::string nombre_musica;
	std::string autor;
public:
	Datos_Musica();
	~Datos_Musica();

	void cargar_midi(std::string direccion);
	void e_pistas(std::vector<Pista> pistas);
	void e_nombre_musica(std::string nombre);
	void e_autor(std::string autor);

	void reiniciar();

	Midi *o_musica();
	std::vector<Pista> *o_pistas();
	std::string o_nombre_musica();
	std::string o_autor();
};

#endif
