#ifndef NOTIFICACION_H
#define NOTIFICACION_H

#include <vector>
#include "elemento.h++"
#include "etiqueta.h++"
#include "../registro.h++"

#define MAXIMAS_NOTIFICACIONES 5

struct Mensaje
{
	Etiqueta *etiqueta = NULL;
	std::string texto = "";
	int tiempo = 0;
	CodigoEstado estado = EstadoNinguno;

	Mensaje(Etiqueta *etiqueta_2, std::string texto_2, int tiempo_2, CodigoEstado estado_2)
	{
		etiqueta = etiqueta_2;
		texto = texto_2;
		tiempo = tiempo_2;
		estado = estado_2;
	}

	~Mensaje()
	{
		if(etiqueta != NULL)
			delete etiqueta;
	}
};

class Notificacion : public Elemento
{
private:
	Administrador_Recursos *m_recursos;
	Textura2D *m_textura_fondo;
	Rectangulo *m_rectangulo;

	std::vector<Etiqueta> m_etiquetas;
	static std::vector<Mensaje *> notificaciones;

	static void Registrar(std::string texto, int tiempo, CodigoEstado estado);

public:
	Notificacion(Administrador_Recursos *recursos);
	~Notificacion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void posicion(int x, int y) override;

	static void Error(std::string texto, int tiempo);
	static void Aviso(std::string texto, int tiempo);
	static void Nota(std::string texto, int tiempo);
	static void Depurar(std::string texto, int tiempo);
};

#endif
