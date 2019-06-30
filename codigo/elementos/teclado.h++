#ifndef TECLADO_H
#define TECLADO_H

#define PROPORCION_BLANCA 6.52941
#define PROPORCION_NEGRA 0.657
#define PROPORCION_ANCHO_NEGRA 0.666667

class Teclado
{
private:
	int numero_blancas, numero_negras;
	int inicio_blanca, inicio_negra;
	int desplazamiento_blancas, desplazamiento_negras;
	int primera_barra;
	bool en_do_primera_barra;

public:
	Teclado();
	Teclado(int numero_b,int numero_n, int inicio_b, int inicio_n, int desplazamiento_b, int desplazamiento_n, int primera_barra, bool en_do_primera_barra);

	int o_numero_blancas();
	int o_numero_negras();

	int o_inicio_blancas();
	int o_inicio_negras();

	int o_desplazamiento_blancas();
	int o_desplazamiento_negras();

	int o_primera_barra();
	bool o_en_do_primera_barra();
};

#endif
