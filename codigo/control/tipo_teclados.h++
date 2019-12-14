#ifndef TIPO_TECLADOS
#define TIPO_TECLADOS

#include <map>
#include "teclado_configuracion.h++"

enum TipoTeclado
{
	Teclas88 = 0,
	Teclas76,
	Teclas61,
	Teclas49,
	Teclas37
};

class Tipo_Teclado
{
private:
	static std::map<TipoTeclado, Teclado_Configuracion> Teclado;
	static std::map<TipoTeclado, Teclado_Configuracion> Cargar_datos();
public:
	static Teclado_Configuracion *Obtener_teclado(TipoTeclado tipo);
};

#endif
