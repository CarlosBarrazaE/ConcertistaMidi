#include "tipo_teclados.h++"

std::map<TipoTeclado, Teclado_Configuracion> Tipo_Teclado::Teclado = Tipo_Teclado::Cargar_datos();

std::map<TipoTeclado, Teclado_Configuracion> Tipo_Teclado::Cargar_datos()
{
	std::map<TipoTeclado, Teclado_Configuracion> temporal;
	temporal[Teclas88] = Teclado_Configuracion(52, 36, 1, 4, 0, 0, 2, true);
	temporal[Teclas76] = Teclado_Configuracion(45, 31, 1, 2, 4, 3, 1, false);
	temporal[Teclas61] = Teclado_Configuracion(36, 25, 0, 0, 9, 6, 0, true);
	temporal[Teclas49] = Teclado_Configuracion(29, 20, 0, 0, 9, 6, 0, true);
	temporal[Teclas37] = Teclado_Configuracion(22, 15, 0, 2, 12, 8, 0, false);
	return temporal;
}

Teclado_Configuracion *Tipo_Teclado::Obtener_teclado(TipoTeclado tipo)
{
	return &Teclado[tipo];
}


