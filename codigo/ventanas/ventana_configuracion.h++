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

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;

	void evento_raton(Raton *raton) override;
	void evento_teclado(Tecla tecla, bool estado) override;
	void evento_pantalla(int ancho, int alto) override;
};
#endif
