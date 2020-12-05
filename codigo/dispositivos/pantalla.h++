#ifndef PANTALLA_H
#define PANTALLA_H

class Pantalla
{
public:
	static float Ancho;
	static float Alto;
	static bool PantallaCompleta;
	static bool ModoAlambre;
	static bool ModoDesarrollo;

	static float Centro_horizontal();
	static float Centro_vertical();
};

#endif
