#ifndef TECLADO_ORGANO
#define TECLADO_ORGANO

#define PROPORCION_BLANCA 6.52941f
#define PROPORCION_NEGRA 0.657f
#define PROPORCION_ANCHO_NEGRA 0.666667f
#define TIEMPO_DETECCION 165000

#include "../util/texto.h++"
#include <vector>

class Teclado_Organo
{
private:
	unsigned int m_tecla_inicial = 0;
	unsigned int m_numero_teclas = 128;
public:
	Teclado_Organo();
	void cambiar(unsigned int inicial, unsigned int largo);

	unsigned int tecla_inicial();
	void tecla_inicial(unsigned int inicial);

	unsigned int numero_teclas();
	void numero_teclas(unsigned int largo);

	void cargar(std::string datos);
	std::string texto();
};

#endif
