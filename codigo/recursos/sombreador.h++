#ifndef SOMBREADOR_H
#define SOMBREADOR_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../registro.h++"

class Sombreador
{
private:
	static unsigned int Ultimo_indice_seleccionado;
	unsigned int m_indice_programa;

	void comprobar_error_sombreador(unsigned int indice) const;
	void comprobar_error_programas(unsigned int indice) const;
	void imprimir_detalle_programa(unsigned int indice) const;
	std::string GL_tipo_a_texto(GLenum tipo) const;
public:
	Sombreador(const char* codigo_vertice, const char* codigo_fragmento);
	~Sombreador();

	void activar();

	unsigned int o_indice();

	void uniforme_bool(const std::string &nombre, bool valor);
	void uniforme_int(const std::string &nombre, int valor);
	void uniforme_float(const std::string &nombre, float valor);
	void uniforme_vector2f(const std::string &nombre, float x, float y);
	void uniforme_vector3f(const std::string &nombre, float x, float y, float z);
	void uniforme_vector4f(const std::string &nombre, float x, float y, float z, float w);
	void uniforme_matriz4(const std::string &nombre, glm::mat4 valor);
};

#endif
