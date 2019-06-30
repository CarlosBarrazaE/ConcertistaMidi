#include "tipo_teclados.h++"

std::map<TipoTeclado, Teclado> Tipo_Teclado::teclado = Tipo_Teclado::cargar_datos();

std::map<TipoTeclado, Teclado> Tipo_Teclado::cargar_datos()
{
	std::map<TipoTeclado, Teclado> temporal;
	temporal[Teclas88] = Teclado(52, 36, 1, 4, 0, 0, 2, true);
	temporal[Teclas76] = Teclado(45, 31, 1, 2, 4, 3, 1, false);
	temporal[Teclas61] = Teclado(36, 25, 0, 0, 9, 6, 0, true);
	temporal[Teclas49] = Teclado(29, 20, 0, 0, 9, 6, 0, true);
	temporal[Teclas37] = Teclado(22, 15, 0, 2, 12, 8, 0, false);
	return temporal;
}

Teclado *Tipo_Teclado::obtener_teclado(TipoTeclado tipo)
{
	return &teclado[tipo];
}


