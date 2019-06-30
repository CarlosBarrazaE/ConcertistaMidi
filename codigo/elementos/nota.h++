#ifndef NOTA_H
#define NOTA_H

class Nota
{
private:
	int tiempo_final;
	int pista;
public:
	Nota();
	Nota(int tiempo_final, int pista);
	~Nota();

	void e_tiempo_final(int valor);
	void e_pista(int valor);
	void e_tiempo_y_pista(int tiempo, int pista);

	int o_tiempo_final();
	int o_pista();
};

#endif
