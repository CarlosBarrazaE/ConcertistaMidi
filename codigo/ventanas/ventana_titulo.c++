#include "ventana_titulo.h++"

VentanaTitulo::VentanaTitulo(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.9f, 0.9f, 0.9f);

	boton_tocar = new Boton(Pantalla::centro_h(), 220, 250, 50, "Tocar una canción", textura, Color(0.145f, 0.707f, 1.0f), true, recursos);
	boton_tocar->e_color_texto(Color(1.0f, 1.0f, 1.0f));
	boton_practicar = new Boton(Pantalla::centro_h(), 280, 250, 50, "Practicar", textura, color, true, recursos);
	boton_configurar = new Boton(Pantalla::centro_h(), 340, 250, 50, "Configuración", textura, color, true, recursos);
	boton_salir = new Boton(Pantalla::centro_h(), 400, 250, 50, "Salir", textura, color, true, recursos);

	textura_fondo = recursos->obtener_textura(T_FondoTitulo);
	textura_titulo = recursos->obtener_textura(T_Titulo);

	rectangulo = recursos->obtener_figura(F_Rectangulo);

	texto_version = recursos->obtener_tipografia(LetraChica);
}

VentanaTitulo::~VentanaTitulo()
{
	delete boton_tocar;
	delete boton_practicar;
	delete boton_configurar;
	delete boton_salir;
}

void VentanaTitulo::actualizar(unsigned int diferencia_tiempo)
{
	boton_tocar->actualizar(diferencia_tiempo);
	boton_practicar->actualizar(diferencia_tiempo);
	boton_configurar->actualizar(diferencia_tiempo);
	boton_salir->actualizar(diferencia_tiempo);
}

void VentanaTitulo::dibujar()
{
	textura_fondo->activar();
	rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	rectangulo->dibujar(0, 0, Pantalla::ancho, 150);
	rectangulo->dibujar(0, Pantalla::alto - 40, Pantalla::ancho, 40);

	textura_titulo->activar();
	rectangulo->dibujar(Pantalla::centro_h() - 256, 30, 512, 128);

	boton_tocar->dibujar();
	boton_practicar->dibujar();
	boton_configurar->dibujar();
	boton_salir->dibujar();

	texto_version->imprimir(20, Pantalla::alto - 15, "Versión: " + std::string(VERSION), Color(1.0f, 1.0f, 1.0f));
}

void VentanaTitulo::evento_raton(Raton *raton)
{
	boton_tocar->evento_raton(raton);
	boton_practicar->evento_raton(raton);
	boton_configurar->evento_raton(raton);
	boton_salir->evento_raton(raton);

	if(boton_tocar->esta_activado())
		this->accion = CambiarASeleccionMusica;
	else if(boton_practicar->esta_activado())
		this->accion = CambiarAOrgano;
	else if(boton_configurar->esta_activado())
		this->accion = CambiarAConfiguracion;
	else if(boton_salir->esta_activado())
		this->accion = Salir;
}

void VentanaTitulo::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && estado)
		this->accion = Salir;
	else if(tecla == TECLA_ENTRAR && !estado)
		this->accion = CambiarASeleccionMusica;
}

void VentanaTitulo::evento_pantalla(int ancho, int alto)
{
	boton_tocar->posicion_x(Pantalla::centro_h());
	boton_practicar->posicion_x(Pantalla::centro_h());
	boton_configurar->posicion_x(Pantalla::centro_h());
	boton_salir->posicion_x(Pantalla::centro_h());
}
