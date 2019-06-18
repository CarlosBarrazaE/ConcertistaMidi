#include "ventana_seleccion_midi.h++"

VentanaSeleccionMusica::VentanaSeleccionMusica(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.9, 0.9, 0.9);

	boton_atras = new Boton(10, Pantalla::alto - 32, 120, 25, "Atras", textura, color, false, recursos);
	boton_continuar = new Boton(Pantalla::ancho - 130, Pantalla::alto - 32, 120, 25, "Continuar", textura, color, false, recursos);

	Texto *texto_boton = recursos->obtener_tipografia(LetraChica);
	boton_atras->e_letra(texto_boton);
	boton_continuar->e_letra(texto_boton);

	Textura2D *textura_fondo = recursos->obtener_textura(T_FondoTitulo);
	Sombreador *sombreador = recursos->obtener_sombreador(Rectangulo_Textura);

	fondo = new Rectangulo(sombreador, textura_fondo);
	texto = recursos->obtener_tipografia(LetraTitulo);
	ajuste_titulo = texto->ancho_texto("Seleccione un archivo para tocar") / 2;
}

VentanaSeleccionMusica::~VentanaSeleccionMusica()
{
	delete fondo;
	delete boton_atras;
	delete boton_continuar;
}

void VentanaSeleccionMusica::actualizar(Raton *raton)
{
	boton_atras->posicion_y(Pantalla::alto - 32);
	boton_atras->actualizar(raton);

	boton_continuar->posicion_x(Pantalla::ancho - 130);
	boton_continuar->posicion_y(Pantalla::alto - 32);
	boton_continuar->actualizar(raton);
	if(boton_atras->esta_activado())
		this->accion = CambiarATitulo;
}

void VentanaSeleccionMusica::dibujar()
{
	fondo->dibujar_rectangulo(0, 0, Pantalla::ancho, 40);
	//fondo->dibujar_rectangulo(0, Pantalla::alto - 40, Pantalla::ancho, 40);
	texto->dibujar_texto(Pantalla::centro_h() - ajuste_titulo, 30, "Seleccione un archivo para tocar", Color(1.0, 1.0, 1.0));
	boton_atras->dibujar();
	boton_continuar->dibujar();
}
