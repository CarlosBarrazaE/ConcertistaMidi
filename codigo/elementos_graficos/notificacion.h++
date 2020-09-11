#ifndef NOTIFICACION_H
#define NOTIFICACION_H

#include "elemento.h++"
#include "etiqueta.h++"
#include "../registro.h++"

class Notificacion : public Elemento
{
private:
	Textura2D *m_textura_fondo;
	Rectangulo *m_rectangulo;

	Etiqueta m_mensaje;
	Color m_color_error, m_color_aviso, m_color_nota, m_color_depurar;
	int m_tiempo_restante;
	CodigoEstado m_estado_mensaje;

	static std::string Texto;
	static int tiempo;
	static CodigoEstado estado;

public:
	Notificacion(Administrador_Recursos *recursos);
	~Notificacion();

	void actualizar(unsigned int diferencia_tiempo) override;
	void dibujar() override;
	void evento_raton(Raton *raton) override;

	void posicion(int x, int y) override;

	void quitar_notificaciones();

	static void Error(std::string texto, int tiempo);
	static void Aviso(std::string texto, int tiempo);
	static void Nota(std::string texto, int tiempo);
	static void Depurar(std::string texto, int tiempo);
};

#endif
