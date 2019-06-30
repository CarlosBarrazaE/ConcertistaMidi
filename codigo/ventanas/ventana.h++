#ifndef VENTANA_H
#define VENTANA_H

#include "../dispositivos/pantalla.h++"
#include "../dispositivos/teclas.h++"
#include "../dispositivos/raton.h++"

enum Accion
{
	Ninguna,
	CambiarATitulo,
	CambiarAConfiguracion,
	CambiarASeleccionMidi,
	CambiarASeleccionPista,
	CambiarAOrgano,
	Salir
};

class Ventana
{
protected:
	Accion accion;
public:
	Ventana();

	virtual void actualizar(Raton *raton) = 0;
	virtual void dibujar() = 0;
	virtual void evento_teclado(Tecla tecla, bool estado) = 0;
	virtual void evento_pantalla(int ancho, int alto) = 0;

	Accion obtener_accion();
};
#endif
