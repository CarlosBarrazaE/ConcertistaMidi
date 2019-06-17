#include "ventana_titulo.h++"

VentanaTitulo::VentanaTitulo(Administrador_Recursos *recursos) : Ventana()
{
	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.7, 0.7, 0.7);

	boton_practicar = new Boton(Pantalla::centro_h(), 200, 250, 50, "Practicar", textura, color, true, recursos);
	boton_tocar = new Boton(Pantalla::centro_h(), 260, 250, 50, "Tocar una canción", textura, color, true, recursos);
	boton_configurar = new Boton(Pantalla::centro_h(), 320, 250, 50, "Configuración", textura, color, true, recursos);
	boton_salir = new Boton(Pantalla::centro_h(), 380, 250, 50, "Salir", textura, color, true, recursos);

	Textura2D *textura_titulo = recursos->obtener_textura(T_Titulo);
	Sombreador *sombreador = recursos->obtener_sombreador(Rectangulo_Textura);
	titulo = new Rectangulo(sombreador, textura_titulo);
}

VentanaTitulo::~VentanaTitulo()
{
	delete titulo;
	delete boton_practicar;
	delete boton_tocar;
	delete boton_configurar;
	delete boton_salir;
}

void VentanaTitulo::actualizar(Raton *raton)
{
	boton_practicar->posicion_x(Pantalla::centro_h());
	boton_tocar->posicion_x(Pantalla::centro_h());
	boton_configurar->posicion_x(Pantalla::centro_h());
	boton_salir->posicion_x(Pantalla::centro_h());

	boton_practicar->actualizar(raton);
	boton_tocar->actualizar(raton);
	boton_configurar->actualizar(raton);
	boton_salir->actualizar(raton);

	if(boton_practicar->esta_activado())
		this->accion = CambiarAPiano;
	else if(boton_tocar->esta_activado())
		this->accion = CambiarASeleccionMidi;
	else if(boton_configurar->esta_activado())
		this->accion = CambiarAConfiguracion;
	else if(boton_salir->esta_activado())
		this->accion = Salir;
}

void VentanaTitulo::dibujar()
{
	titulo->dibujar_rectangulo(Pantalla::centro_h() - 256, 50, 512, 128);
	boton_practicar->dibujar();
	boton_tocar->dibujar();
	boton_configurar->dibujar();
	boton_salir->dibujar();
}
