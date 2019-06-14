#ifndef COLOR_H
#define COLOR_H

class Color
{
private:
	float rojo;
	float verde;
	float azul;
public:
	Color();
	Color(float rojo, float verde, float azul);
	Color(double rojo, double verde, double azul);
	Color(int rojo, int verde, int azul);
	~Color();

	float o_rojo();
	float o_verde();
	float o_azul();

	bool operator == (const Color &c) const;
	bool operator != (const Color &c) const;
};

#endif
