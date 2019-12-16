#ifndef ORGANO_H
#define ORGANO_H

#include "elemento.h++"
#include "../recursos/generador_particulas.h++"
#include "../recursos/rectangulo.h++"
#include "../util/octava.h++"
#include "../control/pista.h++"
#include "../control/teclado_configuracion.h++"
#include "../libmidi/Midi.h++"

#include <map>
#include <vector>

class Organo : public Elemento
{
private:
	Rectangulo *m_rectangulo;

	Textura2D *m_tecla_blanca;
	Textura2D *m_tecla_negra;
	Textura2D *m_tecla_blanca_presionada;
	Textura2D *m_tecla_blanca_presionada_doble;
	Textura2D *m_tecla_negra_presionada;
	Textura2D *m_borde_negro;
	Textura2D *m_borde_rojo;

	Generador_Particulas *m_generador_particulas;
	unsigned int m_tiempo;
	int m_numero_particulas;

	Teclado_Configuracion *m_teclado;
	int m_ancho_real, m_ajuste_x;
	int m_ancho_tecla_blanca, m_ancho_tecla_negra;
	int m_alto_tecla_blanca, m_alto_tecla_negra;

	std::array<Color, 52> *m_teclas_activas_blancas;
	std::array<Color, 36> *m_teclas_activas_negras;

	//Metodos
	void dibujar_blancas(int x, int y, int numero_teclas);
	void dibujar_negras(int x, int y, int numero_teclas);
	void calcular_tamannos();

public:
	Organo(int x, int y, int ancho, Teclado_Configuracion *teclado, Administrador_Recursos *recursos);
	~Organo();

	void ancho(int valor);
	int ancho();
	void c_teclado(Teclado_Configuracion *teclado);

	void e_blancas_presionadas(std::array<Color, 52> *teclas_blancas);
	void e_negras_presionadas(std::array<Color, 36> *teclas_negras);

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();
	void evento_raton(Raton *raton);
	void evento_pantalla(int ancho, int alto);
};

#endif
