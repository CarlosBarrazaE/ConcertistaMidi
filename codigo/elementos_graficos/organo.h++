#ifndef ORGANO_H
#define ORGANO_H

#include "elemento.h++"
#include "../recursos/generador_particulas.h++"
#include "../recursos/rectangulo.h++"
#include "../util/octava.h++"
#include "../control/pista.h++"
#include "../control/teclado_organo.h++"
#include "../libmidi/Midi.h++"
#include "../libmidi/MidiComm.h++"

#include <map>
#include <vector>

#define SIN_NOTA 130

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
	float m_tiempo;
	unsigned int m_numero_particulas;

	Teclado_Organo *m_teclado;
	float m_ancho_tecla_blanca, m_ancho_tecla_negra;
	float m_alto_tecla_blanca, m_alto_tecla_negra;

	std::array<Color, 128> *m_teclas_activas;
	unsigned char m_nota_enviada_anterior;

	//Metodos
	void dibujar_blancas(float x, float y, unsigned int tecla_inicial, unsigned int numero_teclas);
	void dibujar_negras(float x, float y, unsigned int tecla_inicial, unsigned int numero_teclas);

	float desplazamiento_x(unsigned int tecla);

public:
	Organo(float x, float y, float ancho, Teclado_Organo *teclado, Administrador_Recursos *recursos);
	~Organo();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(float ancho, float alto) override;

	void estado_teclas(std::array<Color, 128> *teclas);

	void calcular_tamannos();
};

#endif
