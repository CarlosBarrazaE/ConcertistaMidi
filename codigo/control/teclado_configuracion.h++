#ifndef TECLADO_CONFIGURACION_H
#define TECLADO_CONFIGURACION_H

#define PROPORCION_BLANCA 6.52941f
#define PROPORCION_NEGRA 0.657f
#define PROPORCION_ANCHO_NEGRA 0.666667f

class Teclado_Configuracion
{
private:
	int m_numero_blancas, m_numero_negras;
	int m_inicio_blanca, m_inicio_negra;
	int m_desplazamiento_blancas, m_desplazamiento_negras;
	int m_primera_barra;
	bool m_en_do_primera_barra;

public:
	Teclado_Configuracion();
	Teclado_Configuracion(int numero_b,int numero_n, int inicio_b, int inicio_n, int desplazamiento_b, int desplazamiento_n, int primera_barra, bool en_do_primera_barra);

	int numero_blancas();
	int numero_negras();

	int inicio_blancas();
	int inicio_negras();

	int desplazamiento_blancas();
	int desplazamiento_negras();

	int primera_barra();
	bool en_do_primera_barra();
};

#endif
