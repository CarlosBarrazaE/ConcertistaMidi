#ifndef VENTANACONFIGURACION_H
#define VENTANACONFIGURACION_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../control/configuracion.h++"

class VentanaConfiguracion : public Ventana
{
private:
	//Componentes
	Boton *m_boton_atras;

	//Datos
	Configuracion *m_configuracion;

public:
	VentanaConfiguracion(Configuracion *configuracion, Administrador_Recursos *recursos);
	~VentanaConfiguracion();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
