#ifndef VENTANACONFIGURACION_H
#define VENTANACONFIGURACION_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/solapa.h++"
#include "../control/configuracion.h++"

class VentanaConfiguracion : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;

	//Componentes
	Etiqueta m_texto_titulo;
	Boton *m_boton_atras;
	Solapa *m_solapa;

	//Solapa General (1)
	Etiqueta *m_solapa1_titulo;
	Etiqueta *m_solapa1_texto_restablecer, *m_solapa1_texto_limpiar, *m_solapa1_texto_borrar;
	Boton *m_solapa1_restablecer, *m_solapa1_limpiar_bd, *m_solapa1_borrar_db;

	//Solapa Carpetas MIDI (2)
	Etiqueta *m_solapa2_titulo;

	//Solapa Dispositivos (3)
	Etiqueta *m_solapa3_titulo;

	//Solapa Video (4)
	Etiqueta *m_solapa4_titulo;

	//Datos
	Configuracion *m_configuracion;
	unsigned int m_ultima_solapa;

public:
	VentanaConfiguracion(Configuracion *configuracion, Administrador_Recursos *recursos);
	~VentanaConfiguracion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;

	void evento_raton(Raton *raton) override;
	void evento_teclado(Tecla tecla, bool estado) override;
	void evento_pantalla(float ancho, float alto) override;
};
#endif
