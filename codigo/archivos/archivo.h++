#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <string>
#include <fstream>
#include <sstream>

#include "../registro.h++"

namespace Archivo
{
	std::string leer_archivo(const char* nombre);
}
#endif
