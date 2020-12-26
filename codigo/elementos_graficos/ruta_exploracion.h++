#ifndef RUTA_EXPLORACION_H
#define RUTA_EXPLORACION_H

#include <vector>

#include "elemento.h++"
#include "boton.h++"
#include "../util/funciones.h++"
#include "../util/texto.h++"

class Ruta_Exploracion : public Elemento
{
private:
	//Recursos
	Administrador_Recursos *m_recursos;
	Rectangulo *m_rectangulo;

	//Componentes
	Boton *m_boton_atras, *m_boton_adelante;
	std::vector<Boton*> m_carpetas;

	//Datos
	std::vector<std::string> m_rutas_botones;
	float m_ancho_actual;//Ancho de todos los botones existentes
	unsigned long int m_primera_carpeta_dibujar;
	unsigned long int m_numero_carpeta_extra;
	bool m_agregar_carpeta_extra;
	bool m_cambiar_carpeta;

	void eliminar(unsigned long int inicio);
	void calcular_carpetas_visibles();
public:
	Ruta_Exploracion(float x, float y, float ancho, float alto, Administrador_Recursos *recursos);
	~Ruta_Exploracion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void posicion(float x, float y) override;
	void dimension(float ancho, float alto) override;

	void carpeta_extra(const std::string &nombre, const std::string &ruta);
	void ruta(const std::string &inicio, const std::string &fin);

	void atras();//Cambio a carpeta atras
	bool siguiente();//Ir a carpeta siguiente
	void siguiente_habilitado(bool estado);

	bool cambiar_carpeta();
	std::string nueva_ruta();
};

#endif
