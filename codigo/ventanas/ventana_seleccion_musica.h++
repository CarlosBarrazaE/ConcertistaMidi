#ifndef VENTANASELECCIONMUSICA_H
#define VENTANASELECCIONMUSICA_H

#include <filesystem>
#include <vector>
#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/tabla.h++"
#include "../elementos_graficos/notificacion.h++"
#include "../control/configuracion.h++"
#include "../control/base_de_datos.h++"
#include "../control/datos_musica.h++"
#include "../control/datos_archivos.h++"

class VentanaSeleccionMusica : public Ventana
{
private:
	//Recursos
	Rectangulo *m_rectangulo;
	Etiqueta m_texto_titulo;
	Tabla m_tabla_archivos;

	//Datos
	Configuracion *m_configuracion;
	Datos_Musica *m_musica;
	Base_de_Datos *m_datos;

	std::vector<Datos_Archivos> m_lista_archivos;
	std::string m_carpeta_inicial;
	std::string m_carpeta_activa;
	bool m_es_carpeta_inicial;

	//Componentes
	Boton *m_boton_atras;
	Boton *m_boton_continuar;

	void cargar_lista_carpetas();
	void cargar_contenido_carpeta(std::string ruta_abrir);
	void crear_tabla(std::string ruta_abrir);
	bool abrir_archivo_seleccionado();

public:
	VentanaSeleccionMusica(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;

	void evento_raton(Raton *raton) override;
	void evento_teclado(Tecla tecla, bool estado) override;
	void evento_pantalla(float ancho, float alto) override;
};
#endif
