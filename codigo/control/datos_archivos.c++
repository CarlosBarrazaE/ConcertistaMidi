#include "datos_archivos.h++"

Datos_Archivos::Datos_Archivos()
{
	this->ruta = "";
	this->nombre = "";
	this->fecha_acceso = "Desconocido";
	this->duracion = 0;
	this->visitas = 0;
	this->es_carpeta = false;
	this->tamanno = 0;
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
