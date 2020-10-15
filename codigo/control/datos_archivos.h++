#ifndef DATOS_ARCHIVOS_H
#define DATOS_ARCHIVOS_H

#include <string>
#include "../libmidi/Midi.h++"

struct Datos_Archivos
{
	std::string ruta;
	std::string nombre;
	std::string fecha_acceso;
	microseconds_t duracion;
	unsigned int visitas;
	bool es_carpeta;
	unsigned long int tamanno;

	Datos_Archivos();

	bool operator < (const Datos_Archivos &d) const;
};
#endif
