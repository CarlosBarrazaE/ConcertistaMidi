#ifndef VENTANATITULO_H
#define VENTANATITULO_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../version.h++"

class VentanaTitulo : public Ventana
{
private:
	//Recursos
	Rectangulo *rectangulo;
	Textura2D *textura_fondo, *textura_titulo;
	Texto *texto_version;

	//Componetes
	Boton *boton_practicar;
	Boton *boton_tocar;
	Boton *boton_configurar;
	Boton *boton_salir;
public:
	VentanaTitulo(Administrador_Recursos *recursos);
	~VentanaTitulo();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
