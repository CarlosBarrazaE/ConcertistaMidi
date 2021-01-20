#ifndef VENTANAORGANO_H
#define VENTANAORGANO_H

#include "ventana.h++"
#include "../elementos_graficos/barra_progreso.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/tablero_notas.h++"
#include "../elementos_graficos/organo.h++"
#include "../elementos_graficos/titulo.h++"
#include "../elementos_graficos/puntuacion.h++"
#include "../control/pista.h++"
#include "../control/teclado_organo.h++"
#include "../control/configuracion.h++"
#include "../control/datos_musica.h++"
#include "../control/nota_activa.h++"
#include "../libmidi/Midi.h++"
#include "../libmidi/MidiComm.h++"
#include "../util/texto.h++"

#include <map>
#include <array>

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
	Puntuacion *m_puntaje;
	Etiqueta m_texto_velocidad;
	Etiqueta m_texto_pausa;
	Etiqueta m_subtitulos;
	Etiqueta m_texto_combos;

	//Controles
	double m_velocidad_musica;
	bool m_cambio_velocidad;
	bool m_pausa;
	bool m_retorno_carro;
	bool m_mostrar_subtitulo;
	int m_duracion_nota;

	//Para saver si es necesario guardar
	bool m_guardar_velocidad;
	bool m_guardar_duracion_nota;
	bool m_guardar_tipo_teclado;
	bool m_guardar_estado_subtitulo;

	//Datos
	Teclado_Organo m_teclado_actual;
	Configuracion *m_configuracion;
	Datos_Musica *m_musica;
	NotasPistas m_notas;
	std::string m_subtitulo_texto;
	std::map<unsigned char, Nota_Activa*> m_notas_activas;
	std::array<Color, 128> m_color_teclas_teclas;
	std::array<float, 128> m_tiempo_espera;
	std::vector<unsigned char> m_notas_correctas;
	std::map<unsigned char, Color> m_notas_requeridas;
	std::vector<unsigned int> m_primera_nota;//Ultima nota por cada pista
	std::vector<Pista> *m_pistas;
	microseconds_t m_tiempo_actual_midi;

	void inicializar();
	void reproducir_eventos(unsigned int microsegundos_actualizar);
	void escuchar_eventos();
	void reproducir_subtitulos(const MidiEvent &evento);
	void guardar_configuracion();

	void calcular_teclas_activas(unsigned int diferencia_tiempo);
	void reiniciar();
	void insertar_nota_activa(unsigned char id_nota, unsigned char canal, Color color, bool sonido, bool correcta);
	bool esta_tocada(unsigned char id_nota);
	void eliminar_nota_tocada(unsigned char id_nota);

	void agregar_nota_requerida(unsigned char id_nota, const Color &color);
	void borrar_notas_requeridas();
	bool hay_notas_requeridas();

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
