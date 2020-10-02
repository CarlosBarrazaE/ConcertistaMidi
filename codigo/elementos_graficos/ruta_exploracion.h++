#ifndef RUTA_EXPLORACION
#define RUTA_EXPLORACION

#include <vector>

#include "elemento.h++"
#include "boton.h++"
#include "../util/funciones.h++"

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
	std::vector<std::string> m_rutas_botones;
	bool m_cambiar_carpeta;
	bool m_carpeta_anterior;
	unsigned long int m_posicion_carpeta;

	float m_ancho_anterior;
	float m_largo_actual;
	unsigned long int m_primer_boton_mostrar;

	void calcular_posicion();
public:
	Ruta_Exploracion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Ruta_Exploracion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void dimension(float ancho, float alto) override;

	void ruta_carpeta(const std::string &ruta_inicio, const std::string &ruta_completa, const std::string nombre_carpeta_inicial);

	bool cambiar_carpeta();
	bool boton_siguiente();
	void boton_siguiente_habilitado(bool estado);
	std::string nueva_ruta();
};

#endif
