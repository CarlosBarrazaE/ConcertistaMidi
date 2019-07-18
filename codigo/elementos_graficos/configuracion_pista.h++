#ifndef CONFIGURACION_PISTA_H
#define CONFIGURACION_PISTA_H

#include "elemento.h++"
#include "lista_desplegable.h++"
#include "boton.h++"
#include "../control/pista.h++"
#include <string>

class Configuracion_Pista : public Elemento
{
private:
	//Recursos
	Texto *texto;
	Texto *texto_chico;
	Rectangulo *rectangulo;
	Textura2D *textura_fondo;
	Textura2D *textura_sonido_activado;
	Textura2D *textura_sonido_desactivado;
	Textura2D *textura_reproducir;
	Textura2D *textura_pausar;

	//Componentes
	Lista_Desplegable *seleccion_modo;
	Lista_Desplegable *seleccion_color;
	Boton *vista_previa;
	Boton *boton_sonido;

	//Estados
	bool estado_sonido;
	bool estado_vista_previa;

	//Ajustes
	int centro_texto_sonido;

	//Datos
	Pista datos_pista;

public:
	Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos);
	~Configuracion_Pista();

	Pista o_pista();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
};

#endif
