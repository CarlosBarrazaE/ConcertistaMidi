#ifndef TIPO_TECLADOS
#define TIPO_TECLADOS

#include <map>
#include "teclado.h++"

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
	static std::map<TipoTeclado, Teclado> teclado;
	static std::map<TipoTeclado, Teclado> cargar_datos();
public:
	static Teclado *obtener_teclado(TipoTeclado tipo);
};

#endif
