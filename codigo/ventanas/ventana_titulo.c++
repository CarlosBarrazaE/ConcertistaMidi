#include "ventana_titulo.h++"

VentanaTitulo::VentanaTitulo(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.9, 0.9, 0.9);

	boton_tocar = new Boton(Pantalla::centro_h(), 220, 250, 50, "Tocar una canción", textura, Color(0.145, 0.707, 1.0), true, recursos);
	boton_tocar->e_color_texto(Color(1.0, 1.0, 1.0));
	boton_practicar = new Boton(Pantalla::centro_h(), 280, 250, 50, "Practicar", textura, color, true, recursos);
	boton_configurar = new Boton(Pantalla::centro_h(), 340, 250, 50, "Configuración", textura, color, true, recursos);
	boton_salir = new Boton(Pantalla::centro_h(), 400, 250, 50, "Salir", textura, color, true, recursos);

	Textura2D *textura_fondo = recursos->obtener_textura(T_FondoTitulo);
	Textura2D *textura_titulo = recursos->obtener_textura(T_Titulo);

	Sombreador *sombreador = recursos->obtener_sombreador(Rectangulo_Textura);

	fondo = new Rectangulo(sombreador, textura_fondo);
	titulo = new Rectangulo(sombreador, textura_titulo);

	texto_version = recursos->obtener_tipografia(LetraChica);
}

VentanaTitulo::~VentanaTitulo()
{
	delete fondo;
	delete titulo;
	delete boton_tocar;
	delete boton_practicar;
	delete boton_configurar;
	delete boton_salir;
	delete texto_version;
}

void VentanaTitulo::actualizar(Raton *raton)
{
	boton_tocar->actualizar(raton);
	boton_practicar->actualizar(raton);
	boton_configurar->actualizar(raton);
	boton_salir->actualizar(raton);

	if(boton_tocar->esta_activado())
		this->accion = CambiarASeleccionMidi;
	else if(boton_practicar->esta_activado())
		this->accion = CambiarAOrgano;
	else if(boton_configurar->esta_activado())
		this->accion = CambiarAConfiguracion;
	else if(boton_salir->esta_activado())
		this->accion = Salir;
}

void VentanaTitulo::dibujar()
{
	fondo->dibujar_rectangulo(0, 0, Pantalla::ancho, 150);
	fondo->dibujar_rectangulo(0, Pantalla::alto - 40, Pantalla::ancho, 40);
	titulo->dibujar_rectangulo(Pantalla::centro_h() - 256, 30, 512, 128);
	boton_tocar->dibujar();
	boton_practicar->dibujar();
	boton_configurar->dibujar();
	boton_salir->dibujar();
	texto_version->dibujar_texto(20, Pantalla::alto - 15, "Versión: " + std::string(VERSION), Color(1.0, 1.0, 1.0));
}

void VentanaTitulo::evento_teclado(Tecla tecla, bool estado)
{
}

void VentanaTitulo::evento_pantalla(int ancho, int alto)
{
	boton_tocar->posicion_x(Pantalla::centro_h());
	boton_practicar->posicion_x(Pantalla::centro_h());
	boton_configurar->posicion_x(Pantalla::centro_h());
	boton_salir->posicion_x(Pantalla::centro_h());
}
