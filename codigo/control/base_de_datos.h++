#ifndef BASE_DE_DATOS_H
#define BASE_DE_DATOS_H

#include <sqlite3.h>
#include <string>
#include <vector>

#include "../registro.h++"
#include "../version.h++"

class Base_de_Datos
{
	private:
		bool m_base_de_datos_abierta;
		sqlite3 *m_base_de_datos;
		bool consulta(std::string consulta);
		int consulta_int(std::string consulta);
		std::string consulta_texto(std::string consulta);
	public:
		Base_de_Datos();
		~Base_de_Datos();
		bool abrir(std::string direccion);
		void crear();
		void actualizar();

		//Tabla configuracion
		bool escribir_configuracion(std::string atributo, std::string valor);
		std::string leer_configuracion(std::string atributo);
};

#endif
