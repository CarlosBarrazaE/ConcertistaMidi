#ifndef DATOS_MUSICA_H
#define DATOS_MUSICA_H

#include <vector>
#include "../control/pista.h++"
#include "../libmidi/Midi.h++"
#include "../elementos_graficos/notificacion.h++"

class Datos_Musica
{
private:
	Midi *m_musica;
	std::vector<Pista> m_pistas;

	std::string m_nombre_musica;
	std::string m_autor;
public:
	Datos_Musica();
	~Datos_Musica();

	bool cargar_midi(std::string direccion);
	void pistas(std::vector<Pista> pistas);
	void nombre_musica(std::string nombre);
	void autor(std::string autor);

	void reiniciar();

	Midi *musica();
	std::vector<Pista> *pistas();
	std::string nombre_musica();
	std::string autor();
};

#endif
