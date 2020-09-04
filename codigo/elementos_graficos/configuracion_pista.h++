#ifndef CONFIGURACION_PISTA_H
#define CONFIGURACION_PISTA_H

#include "elemento.h++"
#include "boton.h++"
#include "etiqueta.h++"
#include "lista_opciones.h++"
#include "../control/pista.h++"
#include <string>

class Configuracion_Pista : public Elemento
{
private:
	//Recursos
	Etiqueta m_texto_instrumento, m_texto_notas, m_texto_sonido;
	Rectangulo *m_rectangulo;
	Textura2D *m_textura_fondo;
	Textura2D *m_textura_sonido_activado;
	Textura2D *m_textura_sonido_desactivado;
	Textura2D *m_textura_reproducir;
	Textura2D *m_textura_pausar;

	//Componentes
	Lista_Opciones m_seleccion_modo;
	Lista_Opciones m_seleccion_color;
	Boton *m_vista_previa;
	Boton *m_boton_sonido;

	//Estados
	bool m_estado_vista_previa;

	//Datos
	Pista m_datos_pista;

public:
	Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos);
	~Configuracion_Pista();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void posicion(int x, int y) override;

	Pista pista();
};

#endif
