#include "datos_archivos.h++"

Datos_Archivos::Datos_Archivos()
{
	this->es_carpeta = false;
	this->ruta = "";
	this->nombre = "";
	this->tamanno = 0;
	this->fecha = "Desconocido";
}

bool Datos_Archivos::operator < (const Datos_Archivos &d) const
{
	if(es_carpeta && !d.es_carpeta)
		return true;
	else if(es_carpeta == d.es_carpeta)
	{
		if(nombre < d.nombre)
		return true;
	}
	return false;
}
