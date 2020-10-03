#ifndef TECLADO_CONFIGURACION_H
#define TECLADO_CONFIGURACION_H

#define PROPORCION_BLANCA 6.52941f
#define PROPORCION_NEGRA 0.657f
#define PROPORCION_ANCHO_NEGRA 0.666667f

class Teclado_Configuracion
{
private:
	unsigned int m_numero_blancas, m_numero_negras;
	unsigned int m_inicio_blanca, m_inicio_negra;
	unsigned int m_desplazamiento_blancas, m_desplazamiento_negras;
	unsigned int m_primera_barra;
	bool m_en_do_primera_barra;

public:
	Teclado_Configuracion();
	Teclado_Configuracion(unsigned int numero_b, unsigned int numero_n, unsigned int inicio_b, unsigned int inicio_n, unsigned int desplazamiento_b, unsigned int desplazamiento_n, unsigned int primera_barra, bool en_do_primera_barra);

	unsigned int numero_blancas();
	unsigned int numero_negras();

	unsigned int inicio_blancas();
	unsigned int inicio_negras();

	unsigned int desplazamiento_blancas();
	unsigned int desplazamiento_negras();

	unsigned int primera_barra();
	bool en_do_primera_barra();
};

#endif
