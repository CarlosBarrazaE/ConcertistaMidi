#ifndef OCTAVA_H
#define OCTAVA_H

namespace Octava
{
	bool es_blanca(unsigned int id_nota);
	unsigned int blancas_desde_inicio(unsigned id_nota);
	unsigned int negras_desde_inicio(unsigned id_nota);
	unsigned int numero_blancas(unsigned int inicio, unsigned int largo);
	unsigned int numero_negras(unsigned int inicio, unsigned int largo);
	unsigned int nota_id_desde_blanca(unsigned int blanca_actual);
	float desplazamiento_negra(unsigned int nota);
}

#endif
