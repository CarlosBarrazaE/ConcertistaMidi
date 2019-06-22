#ifndef VENTANA_H
#define VENTANA_H

#include "../raton.h++"

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
	Accion obtener_accion();
};
#endif
