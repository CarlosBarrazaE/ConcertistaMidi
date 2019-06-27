#include "tablero_notas.h++"

Tablero_Notas::Tablero_Notas(int x, int y, int ancho, int alto, Administrador_Recursos *recursos) : Elemento()
{
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->velocidad_caida = 10000;

	this->sombreador = recursos->obtener_sombreador(Rectangulo_Textura);
	this->textura_nota = recursos->obtener_textura(T_Nota);
	this->textura_sombra_nota = recursos->obtener_textura(T_Sombra_Nota);

	this->estructura_nota = new Rectangulo(sombreador, textura_nota, Color(0.2, 0.7, 0.3));
	this->texto = recursos->obtener_tipografia(LetraMuyChica);
}

Tablero_Notas::~Tablero_Notas()
{
}

void Tablero_Notas::e_tiempo(int tiempo)
{
	this->tiempo_actual_midi = tiempo;
}

void Tablero_Notas::e_dimension(int ancho, int alto)
{
	this->ancho = ancho;
	this->alto = alto;
}

void Tablero_Notas::e_notas(TranslatedNoteSet notas)
{
	this->notas = notas;
}

void Tablero_Notas::e_ancho_blanca(int valor)
{
	this->ancho_blanca = valor;
}

void Tablero_Notas::e_ancho_negra(int valor)
{
	this->ancho_negra = valor;
}

void Tablero_Notas::e_ajuste_x(int valor)
{
	this->ajuste_x = valor;
}

void Tablero_Notas::c_velocidad_caida(int valor)
{
	if(valor < 0)
		this->velocidad_caida = this->velocidad_caida - 100;
	else
		this->velocidad_caida = this->velocidad_caida + 100;

	if(this->velocidad_caida < 3500)
		this->velocidad_caida = 3500;
	else if(this->velocidad_caida > 14000)
		this->velocidad_caida = 14000;
}

void Tablero_Notas::actualizar(Raton *raton)
{
}

void Tablero_Notas::dibujar()
{
	this->dibujar_notas(this->textura_sombra_nota);//Dibuja la sombra de la nota
	this->dibujar_notas(this->textura_nota);//Dibuja la nota
}

void Tablero_Notas::dibujar_notas(Textura2D *textura)
{
	textura->activar();
	int ajuste_negra = 0;
	int ancho_tecla = 0;
	int posicion = 0;
	int largo_nota = 0;
	int largo_final = 0;
	int posicion_y = 0;

	Color colores[20];
	colores[0] = Color(0.0, 0.598, 0.0);
	colores[1] = Color(0.0, 0.598, 1.0);
	colores[2] = Color(1.0, 0.598, 1.0);
	colores[3] = Color(1.0, 0.424, 0.0);
	colores[4] = Color(1.0, 0.0, 0.467);
	colores[5] = Color(0.587, 0.0, 0.467);
	colores[6] = Color(0.261, 0.0, 0.467);
	colores[7] = Color(0.0, 0.0, 0.467);
	colores[8] = Color(0.0, 0.761, 0.467);
	colores[9] = Color(0.0, 0.761, 1.0);
	colores[10] = Color(1.0, 0.761, 0.609);
	colores[11] = Color(1.0, 0.761, 0.0);
	colores[12] = Color(0.489, 0.587, 0.489);
	colores[13] = Color(0.489, 0.0, 0.489);
	colores[14] = Color(1.0, 0.0, 0.489);
	colores[15] = Color(0.407, 0.348, 0.408);
	colores[16] = Color(0.407, 0.348, 0.0);
	colores[17] = Color(0.407, 0.348, 1.0);
	colores[18] = Color(0.0, 0.348, 1.0);
	colores[19] = Color(0.0, 0.348, 0.0);
	for(TranslatedNoteSet::const_iterator nota = notas.begin(); nota != notas.end(); ++nota)
	{
		posicion_y = (tiempo_actual_midi - nota->start) / this->velocidad_caida;

		if(posicion_y < -this->alto)
			break;//No se dibujan las notas que aun no entran en la pantalla
		largo_nota = (nota->end - nota->start) / this->velocidad_caida;
		if(posicion_y-largo_nota > 0)
			continue;//No se dibujan las notas que ya salieron de la pantalla

		posicion = Octava::prosicion_nota(nota->note_id);

		this->estructura_nota->seleccionar_color(colores[nota->track_id]);
		if(Octava::es_negra(nota->note_id))
		{
			ancho_tecla = this->ancho_negra;
			int negra = Octava::numero_negra(nota->note_id);
			if(negra==1 || negra == 3)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.667);
			else if(negra==2 || negra == 5)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.333);
			else if(negra==4)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.5);
		}
		else
		{
			ancho_tecla = this->ancho_blanca;
			ajuste_negra = 0;
		}

		//Recorta la parte de la nota que no se ve
		if(posicion_y > 20)
			largo_final = largo_nota - (posicion_y-20);
		else
			largo_final = largo_nota;

		this->estructura_nota->dibujar(ajuste_x + posicion * this->ancho_blanca + ajuste_negra - 2, this->alto + posicion_y-largo_nota - 2, ancho_tecla + 4, largo_final + 4);
	}
}
