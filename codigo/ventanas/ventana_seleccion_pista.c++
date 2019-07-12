#include "ventana_seleccion_pista.h++"

VentanaSeleccionPista::VentanaSeleccionPista(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.9f, 0.9f, 0.9f);

	boton_atras = new Boton(10, Pantalla::alto - 32, 120, 25, "Atrás", textura, color, false, recursos);
	boton_continuar = new Boton(Pantalla::ancho - 130, Pantalla::alto - 32, 120, 25, "Continuar", textura, color, false, recursos);

	Texto *texto_boton = recursos->obtener_tipografia(LetraChica);
	boton_atras->e_letra(texto_boton);
	boton_continuar->e_letra(texto_boton);

	rectangulo = recursos->obtener_figura(F_Rectangulo);
	texto = recursos->obtener_tipografia(LetraTitulo);
	ajuste_titulo = texto->ancho_texto("Selección de Pistas") / 2;
}

VentanaSeleccionPista::~VentanaSeleccionPista()
{
	delete boton_atras;
	delete boton_continuar;
}

void VentanaSeleccionPista::actualizar(unsigned int diferencia_tiempo)
{
	boton_atras->actualizar(diferencia_tiempo);
	boton_continuar->actualizar(diferencia_tiempo);
}

void VentanaSeleccionPista::dibujar()
{
	rectangulo->textura(false);
	rectangulo->dibujar(0, 0, Pantalla::ancho, 40, Color(0.141f, 0.624f, 0.933f));
	rectangulo->dibujar(0, Pantalla::alto - 40, Pantalla::ancho, 40, Color(0.761f, 0.887f, 0.985f));
	texto->imprimir(Pantalla::centro_h() - ajuste_titulo, 30, "Selección de Pistas", Color(1.0f, 1.0f, 1.0f));

	boton_atras->dibujar();
	boton_continuar->dibujar();
}

void VentanaSeleccionPista::evento_raton(Raton *raton)
{
	boton_atras->evento_raton(raton);
	boton_continuar->evento_raton(raton);

	if(boton_atras->esta_activado())
		this->accion = CambiarASeleccionMusica;

	if(boton_continuar->esta_activado())
		this->accion = CambiarAOrgano;
}

void VentanaSeleccionPista::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		this->accion = CambiarASeleccionMusica;
	else if(tecla == TECLA_ENTRAR && !estado)
		this->accion = CambiarAOrgano;
}

void VentanaSeleccionPista::evento_pantalla(int ancho, int alto)
{
	boton_atras->posicion_y(alto - 32);

	boton_continuar->posicion_x(ancho - 130);
	boton_continuar->posicion_y(alto - 32);
}
