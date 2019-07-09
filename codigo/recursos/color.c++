#include "color.h++"

Color::Color()
{
	this->establecer_valores(0.0f, 0.0f, 0.0f, 1.0f);
}

Color::Color(int rojo, int verde, int azul)
{
	this->establecer_valores(rojo / 254.0f, verde / 254.0f, azul / 254.0f, 1.0);
}

Color::Color(float rojo, float verde, float azul)
{
	this->establecer_valores(rojo, verde, azul, 1.0f);
}

Color::Color(int rojo, int verde, int azul, int alfa)
{
	this->establecer_valores(rojo / 254.0f, verde / 254.0f, azul / 254.0f, alfa / 254.0f);
}

Color::Color(float rojo, float verde, float azul, float alfa)
{
	this->establecer_valores(rojo, verde, azul, alfa);
}

Color::~Color()
{
}

float Color::valor_limitado(float valor)
{
	//Limita el valor entre 0 y 1
	if(valor < 0.0f)
		return 0.0f;
	else if(valor > 1.0f)
		return 1.0f;
	else
		return valor;
}

void Color::establecer_valores(float rojo, float verde, float azul, float alfa)
{
	this->rojo = this->valor_limitado(rojo);
	this->verde = this->valor_limitado(verde);
	this->azul = this->valor_limitado(azul);
	this->alfa = this->valor_limitado(alfa);
}

void Color::e_color(int rojo, int verde, int azul)
{
	this->establecer_valores(rojo / 254.0f, verde / 254.0f, azul / 254.0f, 1.0f);
}

void Color::e_color(float rojo, float verde, float azul)
{
	this->establecer_valores(rojo, verde, azul, 1.0f);
}

void Color::e_color(int rojo, int verde, int azul, int alfa)
{
	this->establecer_valores(rojo / 254.0f, verde / 254.0f, azul / 254.0f, alfa / 254.0f);
}

void Color::e_color(float rojo, float verde, float azul, float alfa)
{
	this->establecer_valores(rojo, verde, azul, alfa);
}

float Color::o_rojo()
{
	return this->rojo;
}

float Color::o_verde()
{
	return this->verde;
}

float Color::o_azul()
{
	return this->azul;
}

float Color::o_alfa()
{
	return this->alfa;
}

void Color::c_rojo(float valor)
{
	this->rojo = this->valor_limitado(this->rojo+valor);
}

void Color::c_verde(float valor)
{
	this->verde = this->valor_limitado(this->verde+valor);
}

void Color::c_azul(float valor)
{
	this->azul = this->valor_limitado(this->azul+valor);
}

void Color::c_alfa(float valor)
{
	this->alfa = this->valor_limitado(this->alfa+valor);
}

void Color::c_tono(float valor)
{
	this->rojo = this->valor_limitado(this->rojo+valor);
	this->verde = this->valor_limitado(this->verde+valor);
	this->azul = this->valor_limitado(this->azul+valor);
}

bool Color::operator == (const Color &c) const
{
	return this->rojo == c.rojo && this->verde == c.verde && this->azul == c.azul && this->alfa == c.alfa;
}

bool Color::operator != (const Color &c) const
{
	return this->rojo != c.rojo || this->verde != c.verde || this->azul != c.azul || this->alfa != c.alfa;
}

Color& Color::operator = (const Color &c)
{
	if(this != &c)
	{
		this->rojo = c.rojo;
		this->verde = c.verde;
		this->azul = c.azul;
		this->alfa = c.alfa;
	}
	return *this;
}

Color& Color::operator + (const Color &c)
{
	this->rojo = this->valor_limitado(this->rojo + c.rojo);
	this->verde = this->valor_limitado(this->verde + c.verde);
	this->azul = this->valor_limitado(this->azul + c.azul);
	this->alfa = this->valor_limitado(this->alfa + c.alfa);
	return *this;
}

Color& Color::operator - (const Color &c)
{
	this->rojo = this->valor_limitado(this->rojo - c.rojo);
	this->verde = this->valor_limitado(this->verde - c.verde);
	this->azul = this->valor_limitado(this->azul - c.azul);
	this->alfa = this->valor_limitado(this->alfa - c.alfa);
	return *this;
}

Color& Color::operator + (const float &valor)
{
	this->rojo = this->valor_limitado(this->rojo + valor);
	this->verde = this->valor_limitado(this->verde + valor);
	this->azul = this->valor_limitado(this->azul + valor);
	return *this;
}

Color& Color::operator - (const float &valor)
{
	this->rojo = this->valor_limitado(this->rojo - valor);
	this->verde = this->valor_limitado(this->verde - valor);
	this->azul = this->valor_limitado(this->azul - valor);
	return *this;
}
