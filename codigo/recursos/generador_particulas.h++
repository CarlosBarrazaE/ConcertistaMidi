#ifndef GENERADOR_PARTICULAS_H
#define GENERADOR_PARTICULAS_H

#include "particula.h++"
#include "figura.h++"
#include "textura_2d.h++"
#include "color.h++"
#include "../util/funciones.h++"

#include <vector>

class Generador_Particulas : public Figura
{
private:
	static float Ultima_escala;
	static Color Color_anterior;

	Textura2D *m_textura;
	unsigned int m_indice_objeto;

	std::vector<Particula> m_particulas;

	unsigned int m_particulas_activas;
	unsigned int m_particulas_maximas;
	unsigned int m_primera_particula_activa;
	unsigned int m_ultima_particula_activa;

	float m_tiempo;
	float m_escala;

	unsigned int particula_inactiva();

public:
	Generador_Particulas(Sombreador *sombreador, Textura2D *textura, unsigned int particulas_maximas, float escala);
	~Generador_Particulas();
	void escala(float escala);

	void actualizar(float tiempo);
	void dibujar();
	void agregar_particulas(float x, float y, unsigned int cantidad_particulas, Color color);
};

#endif
