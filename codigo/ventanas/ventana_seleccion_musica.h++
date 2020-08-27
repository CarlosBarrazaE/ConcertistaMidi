#ifndef VENTANASELECCIONMUSICA_H
#define VENTANASELECCIONMUSICA_H

#include <filesystem>
#include <vector>
#include "ventana.h++"
#include "../elementos_graficos/boton.h++"
#include "../elementos_graficos/etiqueta.h++"
#include "../elementos_graficos/tabla.h++"
#include "../control/configuracion.h++"
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

	std::vector<Datos_Archivos> m_lista_archivos;
	std::vector<std::string> m_rutas;

	//Componentes
	Boton *m_boton_atras;
	Boton *m_boton_continuar;

	void cargar_carpeta(std::string ruta_abrir, bool guardar_ruta);
	bool abrir_archivo_seleccionado();

public:
	VentanaSeleccionMusica(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos);
	~VentanaSeleccionMusica();

	void actualizar(unsigned int diferencia_tiempo);
	void dibujar();

	void evento_raton(Raton *raton);
	void evento_teclado(Tecla tecla, bool estado);
	void evento_pantalla(int ancho, int alto);
};
#endif
