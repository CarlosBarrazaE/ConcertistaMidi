#ifndef SELECTOR_ARCHIVOS_H
#define SELECTOR_ARCHIVOS_H

#include "elemento.h++"
#include "ruta_exploracion.h++"
#include "tabla.h++"
#include "boton.h++"
#include "../control/datos_archivos.h++"

enum Dialogo
{
	Esperar = 0,
	Aceptar = 1,
	Cancelar = 2,
};

class Selector_Archivos : public Elemento
{
private:
	//Recursos
	Rectangulo *m_rectangulo;

	//Elementos
	Etiqueta m_titulo;
	Ruta_Exploracion m_ruta;
	Tabla m_tabla;
	Boton *m_cancelar, *m_aceptar;

	//Datos
	Dialogo m_dialogo;
	std::string m_ruta_actual;
	bool m_mostrar_archivos;
	std::vector<Datos_Archivos> m_lista_archivos;

	void cargar_tabla(std::string ruta_abrir);
public:
	Selector_Archivos(float x, float y, float ancho, float alto, std::string titulo, std::string ruta, bool mostrar_archivos, Administrador_Recursos *recursos);
	~Selector_Archivos();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;
	void posicion(float x, float y) override;

	Dialogo dialogo();
	std::string ruta_seleccionada();
};

#endif
