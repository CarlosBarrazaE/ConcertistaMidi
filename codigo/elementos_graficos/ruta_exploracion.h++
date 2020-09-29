#ifndef RUTA_EXPLORACION
#define RUTA_EXPLORACION

#include <vector>

#include "elemento.h++"
#include "boton.h++"

class Ruta_Exploracion : public Elemento
{
private:
	//Recursos
	Administrador_Recursos *m_recursos;
	Rectangulo *m_rectangulo;

	//Componentes
	Boton *m_boton_atraz, *m_boton_adelante;
	std::vector<Boton*> m_carpetas;

	//Datos
	unsigned int m_carpeta_seleccionada;
public:
	Ruta_Exploracion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Ruta_Exploracion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(float ancho, float alto) override;
};

#endif
