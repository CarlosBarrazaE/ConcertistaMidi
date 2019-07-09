#ifndef GENERADOR_PARTICULAS_H
#define GENERADOR_PARTICULAS_H

#include "particula.h++"
#include "figura.h++"
#include "textura_2d.h++"
#include "color.h++"

#include <vector>

class Generador_Particulas : public Figura
{
private:
	static int ultima_escala;
	static Color color_anterior;

	Textura2D *textura;
	unsigned int indice_objeto;

	std::vector<Particula> particulas;

	unsigned int particulas_activas;
	unsigned int particulas_maximas;
	unsigned int primera_particula_activa;
	unsigned int ultima_particula_activa;

	float tiempo;
	int escala;

	int obtener_particula_inactiva();

public:
	Generador_Particulas(Sombreador *sombreador, Textura2D *textura, unsigned int particulas_maximas, int escala);
	~Generador_Particulas();
	void e_escala(int escala);

	void actualizar(float tiempo);
	void dibujar();
	void agregar_particulas(int x, int y, unsigned int cantidad_particulas, Color color);
};

#endif
