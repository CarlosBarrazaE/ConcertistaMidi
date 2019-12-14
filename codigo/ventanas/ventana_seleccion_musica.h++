#ifndef VENTANASELECCIONMUSICA_H
#define VENTANASELECCIONMUSICA_H

#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/etiqueta.h++"

class VentanaSeleccionMusica : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Etiqueta m_texto_titulo;

	//Componentes
	Boton *m_boton_atras;
	Boton *m_boton_continuar;
public:
	VentanaSeleccionMusica(Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
