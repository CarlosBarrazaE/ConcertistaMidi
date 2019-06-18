#ifndef VENTANATITULO_H
#define VENTANATITULO_H

#include "ventana.h++"
#include "../elementos/boton.h++"
#include "../raton.h++"
#include "../recursos/textura_2d.h++"
#include "../recursos/sombreador.h++"
#include "../recursos/rectangulo.h++"
#include "../pantalla.h++"
#include "../version.h++"

class VentanaTitulo : public Ventana
{
private:
	Rectangulo *fondo;
	Rectangulo *titulo;

	Boton *boton_practicar;
	Boton *boton_tocar;
	Boton *boton_configurar;
	Boton *boton_salir;

	Texto *texto_version;
public:
	VentanaTitulo(Administrador_Recursos *recursos);
	~VentanaTitulo();

	void actualizar(Raton *raton);
	void dibujar();
};
#endif
