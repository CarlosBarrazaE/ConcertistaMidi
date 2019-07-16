#include "organo.h++"

Organo::Organo(int x, int y, int ancho, Teclado *teclado, Administrador_Recursos *recursos) : Elemento(x, y, ancho, 0)
{
	//El origen del organo esta abajo a la izquierda
	this->teclado = teclado;
	this->calcular_tamannos();

	this->tecla_blanca = recursos->obtener_textura(T_TeclaBlanca);
	this->tecla_negra = recursos->obtener_textura(T_TeclaNegra);

	this->tecla_blanca_presionada = recursos->obtener_textura(T_TeclaBlancaPresionada);
	this->tecla_blanca_presionada_doble = recursos->obtener_textura(T_TeclaBlancaPresionadaDoble);
	this->tecla_negra_presionada = recursos->obtener_textura(T_TeclaNegraPresionada);

	this->borde_negro = recursos->obtener_textura(T_BordeOrganoNegro);
	this->borde_rojo = recursos->obtener_textura(T_BordeOrganoRojo);

	this->rectangulo = recursos->obtener_figura(F_Rectangulo);

	Sombreador *particulas = recursos->obtener_sombreador(S_Particula);
	Textura2D *t_particula = recursos->obtener_textura(T_ParticulaNota);
	this->generador_particulas = new Generador_Particulas(particulas, t_particula, 500, this->ancho_tecla_blanca);
}

Organo::~Organo()
{
}

void Organo::calcular_tamannos()
{
	this->ancho_tecla_blanca = (this->ancho / this->teclado->o_numero_blancas());
	this->alto_tecla_blanca = this->ancho_tecla_blanca * PROPORCION_BLANCA;
	if(this->alto_tecla_blanca > 250)
		this->alto_tecla_blanca = 250;

	this->ancho_tecla_negra = this->ancho_tecla_blanca * PROPORCION_ANCHO_NEGRA;
	this->alto_tecla_negra = this->alto_tecla_blanca * PROPORCION_NEGRA;

	this->alto = this->alto_tecla_blanca + 11;

	//Diferencia producida porque no se puede dibujar menos de un pixel
	this->ancho_real = this->ancho_tecla_blanca * this->teclado->o_numero_blancas();
	this->ajuste_x = (this->ancho - this->ancho_real) / 2;
}

void Organo::e_ancho(int valor)
{
	this->ancho = valor;
	this->calcular_tamannos();
	this->generador_particulas->e_escala(this->ancho_tecla_blanca);
}

void Organo::c_teclado(Teclado *teclado)
{
	this->teclado = teclado;
	this->calcular_tamannos();
	this->generador_particulas->e_escala(this->ancho_tecla_blanca);
}

void Organo::e_blancas_presionadas(std::array<Color, 52> *teclas_blancas)
{
	this->teclas_activas_blancas = teclas_blancas;
}

void Organo::e_negras_presionadas(std::array<Color, 36> *teclas_negras)
{
	this->teclas_activas_negras = teclas_negras;
}

void Organo::actualizar(unsigned int diferencia_tiempo)
{
	this->generador_particulas->actualizar(((double)diferencia_tiempo/1000000000.0)*3);
}

void Organo::dibujar()
{
	rectangulo->textura(false);
	rectangulo->dibujar(this->x, this->y - this->alto, this->ancho, this->alto, Color(0.0f, 0.0f, 0.0f));

	tecla_blanca->activar();
	rectangulo->textura(true);
	rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	this->dibujar_blancas(this->x + this->ajuste_x, this->y - this->alto + 10, this->teclado->o_numero_blancas());

	tecla_negra->activar();
	this->dibujar_negras(this->x + this->ajuste_x, this->y - this->alto + 10, this->teclado->o_numero_negras());

	borde_negro->activar();
	rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	rectangulo->dibujar(this->x, this->y - this->alto, this->ancho, 5);

	borde_rojo->activar();
	rectangulo->dibujar(this->x + this->ajuste_x, this->y - this->alto + 5, this->ancho_real-1, 5);

	this->generador_particulas->dibujar();
}

void Organo::evento_raton(Raton *raton)
{
}

void Organo::dibujar_blancas(int x, int y, int numero_teclas)
{
	int desplazamiento = x;
	Color negro;
	bool tecla_presionada_anterior = false;
	for(int n=0; n<numero_teclas; n++)
	{
		if(teclas_activas_blancas->at(n) != negro)
		{
			rectangulo->color(teclas_activas_blancas->at(n));
			this->generador_particulas->agregar_particulas(desplazamiento + this->ancho_tecla_blanca/2.0 - this->ancho_tecla_blanca/2, y, 2, teclas_activas_blancas->at(n));
			teclas_activas_blancas->at(n) = negro;
			if(tecla_presionada_anterior)
				tecla_blanca_presionada_doble->activar();
			else
				tecla_blanca_presionada->activar();
			tecla_presionada_anterior = true;
		}
		else
		{
			tecla_blanca->activar();
			rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			tecla_presionada_anterior = false;
		}

		rectangulo->dibujar(desplazamiento, y, this->ancho_tecla_blanca - 1, this->alto_tecla_blanca);
		desplazamiento += this->ancho_tecla_blanca;
	}
}

void Organo::dibujar_negras(int x, int y, int numero_teclas)
{
	int desplazamiento = 0;
	int n_blanca = this->teclado->o_inicio_blancas();
	int n_negra = this->teclado->o_inicio_negras();
	Color negro;
	Color color_actual;
	bool tecla_activa = false;
	for(int n=0; n<numero_teclas; n++)
	{
		if(teclas_activas_negras->at(n) != negro)
		{
			rectangulo->color(teclas_activas_negras->at(n));
			color_actual = teclas_activas_negras->at(n);
			teclas_activas_negras->at(n) = negro;
			tecla_negra_presionada->activar();
			tecla_activa = true;
		}
		else
		{
			rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			tecla_negra->activar();
			tecla_activa = false;
		}
		if(n_negra==0 || n_negra == 2)
		{
			n_blanca++;
			desplazamiento = x + n_blanca * this->ancho_tecla_blanca - this->ancho_tecla_negra * 0.667;
		}
		else if(n_negra==1 || n_negra == 4)
			desplazamiento = x + n_blanca * this->ancho_tecla_blanca - this->ancho_tecla_negra * 0.333;
		else if(n_negra==3)
			desplazamiento = x + n_blanca * this->ancho_tecla_blanca - this->ancho_tecla_negra * 0.5;

		n_negra++;
		n_blanca++;
		if(n_negra == 5)
			n_negra = 0;

		if(tecla_activa)
			this->generador_particulas->agregar_particulas(desplazamiento + this->ancho_tecla_negra/2.0 - this->ancho_tecla_blanca/2, y, 2, color_actual-0.2f);
		//El ancho de la tecla mas el ancho de la sombra
		rectangulo->dibujar(desplazamiento, y, this->ancho_tecla_negra + this->ancho_tecla_negra * 0.22, this->alto_tecla_negra);
	}
}
