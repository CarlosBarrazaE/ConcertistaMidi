#ifndef PUNTUACION_H
#define PUNTUACION_H

#define COMBO_MINIMO_MOSTRAR 4

#include "elemento.h++"
#include "etiqueta.h++"

#include <vector>

struct Puntos
{
	microseconds_t tiempo = 0;
	int puntaje = 0;
};

class Puntuacion : public Elemento
{
private:
	Rectangulo *m_rectangulo;

	Etiqueta m_texto_puntaje, m_texto_aciertos, m_texto_maxcombo, m_texto_errores;

	//Datos
	std::vector<Puntos> m_puntuacion;
	microseconds_t m_ultimo_tiempo;
	int m_puntaje_total;
	unsigned int m_notas_totales;
	unsigned int m_notas_tocadas;
	int m_errores;
	unsigned int m_maximo_combo;
	unsigned int m_combos;

public:
	Puntuacion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Puntuacion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void nota_correcta(unsigned int cantidad, microseconds_t tiempo, double velocidad);
	void notas_totales(unsigned int total_nota);
	void cambiar_a(microseconds_t tiempo_nuevo);
	void sumar_error();

	void combo(unsigned int combo);
	unsigned int combo();
	void reiniciar_combo();
};

#endif
