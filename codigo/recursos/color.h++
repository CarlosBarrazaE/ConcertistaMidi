#ifndef COLOR_H
#define COLOR_H

class Color
{
private:
	float rojo;
	float verde;
	float azul;
	float alfa;

	float valor_limitado(float valor);
	void establecer_valores(float rojo, float verde, float azul, float alfa);
public:
	Color();
	Color(int rojo, int verde, int azul);
	Color(float rojo, float verde, float azul);

	Color(int rojo, int verde, int azul, int alfa);
	Color(float rojo, float verde, float azul, float alfa);
	~Color();

	void e_color(int rojo, int verde, int azul);
	void e_color(float rojo, float verde, float azul);

	void e_color(int rojo, int verde, int azul, int alfa);
	void e_color(float rojo, float verde, float azul, float alfa);

	void c_rojo(float valor);
	void c_verde(float valor);
	void c_azul(float valor);
	void c_alfa(float valor);
	void c_tono(float valor);

	float o_rojo();
	float o_verde();
	float o_azul();
	float o_alfa();

	bool operator == (const Color &c) const;
	bool operator != (const Color &c) const;
	Color& operator = (const Color &c);
	Color& operator + (const Color &c);
	Color& operator - (const Color &c);

	Color& operator + (const float &valor);
	Color& operator - (const float &valor);
};

#endif
