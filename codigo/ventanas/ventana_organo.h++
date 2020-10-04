#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../elementos_graficos/barra_progreso.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/tablero_notas.h++"
#include "../elementos_graficos/organo.h++"
#include "../elementos_graficos/titulo.h++"
#include "../control/pista.h++"
#include "../control/tipo_teclados.h++"
#include "../control/configuracion.h++"
#include "../control/datos_musica.h++"
#include "../libmidi/Midi.h++"
#include "../libmidi/MidiComm.h++"
#include <map>

class VentanaOrgano : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Textura2D *m_textura_subtitulo;

	//Componentes
	Barra_Progreso *m_barra;
	Tablero_Notas *m_tablero;
	Organo *m_organo;
	Titulo *m_titulo_musica;
	Etiqueta m_texto_velocidad;
	Etiqueta m_texto_pausa;
	Etiqueta m_subtitulos;

	//Controles
	double m_velocidad_musica;
	bool m_cambio_velocidad;
	bool m_pausa;
	bool m_retorno_carro;

	//Para saver si es necesario guardar
	bool m_guardar_velocidad;
	bool m_guardar_duracion_nota;
	bool m_guardar_tipo_teclado;

	//Datos
	Configuracion *m_configuracion;
	Datos_Musica *m_musica;
	std::array<Color, 52> *m_teclas_activas_blancas;
	std::array<Color, 36> *m_teclas_activas_negras;
	std::set<unsigned int> m_notas_tocadas_blanca;
	std::set<unsigned int> m_notas_tocadas_negra;
	TipoTeclado m_teclado_actual;
	std::string m_subtitulo_texto;

	void guardar_configuracion();

public:
	VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaOrgano();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;

	void evento_raton(Raton *raton) override;
	void evento_teclado(Tecla tecla, bool estado) override;
	void evento_pantalla(float ancho, float alto) override;
};
#endif
