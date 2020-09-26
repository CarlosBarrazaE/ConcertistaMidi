#ifndef LISTA_OPCIONES_H
#define LISTA_OPCIONES_H

#include "elemento.h++"
#include "etiqueta.h++"
#include <vector>
#include <string>

class Lista_Opciones : public Elemento
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Etiqueta m_texto_seleccion;

	std::vector<std::string> m_opciones;
	std::vector<Textura2D*> m_iconos;
	bool m_usar_iconos = false;

	bool m_sobre_boton;
	BotonRaton m_boton_pre_activado;
	bool m_boton_izquierdo;
	bool m_boton_central;
	bool m_boton_derecho;
	bool m_cambio_opcion_seleccionada;

	float m_centrado_icono;
	float m_ancho_icono, m_alto_icono;
	unsigned int m_opcion_actual;
public:
	Lista_Opciones(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Lista_Opciones();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void posicion(float x, float y) override;

	void dimension_icono(float ancho, float alto);
	void opciones_textos(std::vector<std::string> opciones);
	void opciones_iconos(std::vector<Textura2D*> iconos);
	void tipografia(Tipografia *tipografia);
	void opcion_predeterminada(unsigned int opcion);
	unsigned int opcion_seleccionada();
	bool cambio_opcion_seleccionada();
};

#endif
