#ifndef VENTANATITULO_H
#define VENTANATITULO_H

#include "ventana.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/boton.h++"
#include "../version.h++"

class VentanaTitulo : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Textura2D *m_textura_fondo, *m_textura_titulo;
	Etiqueta m_texto_version;

	//Componetes
	Boton *m_boton_tocar;
	Boton *m_boton_practicar;
	Boton *m_boton_configurar;
	Boton *m_boton_salir;
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
