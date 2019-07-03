#include "organo.h++"

Organo::Organo(int x, int y, int ancho, Teclado *teclado, Administrador_Recursos *recursos) : Elemento()
{
	//El origen del organo esta abajo a la izquierda
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->teclado = teclado;
	this->calcular_tamannos();

	sombreador = recursos->obtener_sombreador(Rectangulo_SinTextura);
	sombreador2 = recursos->obtener_sombreador(Rectangulo_Textura);
	fondo = new Rectangulo(sombreador, Color(0.2, 0.7, 0.3));

	tecla_blanca = recursos->obtener_textura(T_TeclaBlanca);
	tecla_negra = recursos->obtener_textura(T_TeclaNegra);
	tecla_negra_presionada = recursos->obtener_textura(T_TeclaNegraPresionada);
	borde_negro = recursos->obtener_textura(T_BordeOrganoNegro);
	borde_rojo = recursos->obtener_textura(T_BordeOrganoRojo);
	teclas = new Rectangulo(sombreador2, tecla_blanca, Color(1.0, 1.0, 1.0));
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

int Organo::o_alto()
{
	return this->alto;
}

void Organo::e_y(int valor)
{
	this->y = valor;
}

void Organo::e_ancho(int valor)
{
	this->ancho = valor;
	this->calcular_tamannos();
}

void Organo::c_teclado(Teclado *teclado)
{
	this->teclado = teclado;
	this->calcular_tamannos();
}

void Organo::e_blancas_presionadas(std::array<Color, 52> *teclas_blancas)
{
	this->teclas_activas_blancas = teclas_blancas;
}

void Organo::e_negras_presionadas(std::array<Color, 36> *teclas_negras)
{
	this->teclas_activas_negras = teclas_negras;
}

void Organo::actualizar(Raton *raton)
{

}

void Organo::dibujar()
{
	fondo->dibujar_rectangulo(this->x, this->y - this->alto, this->ancho, this->alto, Color(0.0, 0.0, 0.0));

	tecla_blanca->activar();
	teclas->seleccionar_color(Color(1.0, 1.0, 1.0));
	this->dibujar_blancas(this->x + this->ajuste_x, this->y - this->alto + 10, this->teclado->o_numero_blancas());

	tecla_negra->activar();
	this->dibujar_negras(this->x + this->ajuste_x, this->y - this->alto + 10, this->teclado->o_numero_negras());

	borde_negro->activar();
	teclas->seleccionar_color(Color(1.0, 1.0, 1.0));
	teclas->dibujar(this->x, this->y - this->alto, this->ancho, 5);

	borde_rojo->activar();
	teclas->dibujar(this->x + this->ajuste_x, this->y - this->alto + 5, this->ancho_real-1, 5);
}

void Organo::dibujar_blancas(int x, int y, int numero_teclas)
{
	int desplazamiento = x;
	Color negro = Color(0.0, 0.0, 0.0);
	for(int n=0; n<numero_teclas; n++)
	{
		if(teclas_activas_blancas->at(n) != negro)
		{
			teclas->seleccionar_color(teclas_activas_blancas->at(n));
			teclas_activas_blancas->at(n) = negro;
		}
		else
			teclas->seleccionar_color(Color(1.0, 1.0, 1.0));
		teclas->dibujar(desplazamiento, y, this->ancho_tecla_blanca - 1, this->alto_tecla_blanca);
		desplazamiento += this->ancho_tecla_blanca;
	}
}

void Organo::dibujar_negras(int x, int y, int numero_teclas)
{
	int desplazamiento = 0;
	int n_blanca = this->teclado->o_inicio_blancas();
	int n_negra = this->teclado->o_inicio_negras();
	Color negro = Color(0.0, 0.0, 0.0);
	for(int n=0; n<numero_teclas; n++)
	{
		if(teclas_activas_negras->at(n) != negro)
		{
			teclas->seleccionar_color(teclas_activas_negras->at(n));
			teclas_activas_negras->at(n) = negro;
			tecla_negra_presionada->activar();
		}
		else
		{
			teclas->seleccionar_color(Color(1.0, 1.0, 1.0));
			tecla_negra->activar();
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

		//El ancho de la tecla mas el ancho de la sombra
		teclas->dibujar(desplazamiento, y, this->ancho_tecla_negra + this->ancho_tecla_negra * 0.22, this->alto_tecla_negra);
	}
}
