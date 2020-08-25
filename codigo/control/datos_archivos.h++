#ifndef DATOS_ARCHIVOS_H
#define DATOS_ARCHIVOS_H

#include <string>

struct Datos_Archivos
{
	bool es_carpeta;
	std::string ruta;
	std::string nombre;
	int tamanno;
	std::string fecha;

	Datos_Archivos();

	bool operator < (const Datos_Archivos &d) const;
};
#endif
