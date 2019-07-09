#include "tablero_notas.h++"

Tablero_Notas::Tablero_Notas(int x, int y, int ancho, int alto, Teclado *teclado, Administrador_Recursos *recursos) : Elemento()
{
	this->x = x;
	this->y = y;
	this->ancho = ancho;
	this->alto = alto;
	this->velocidad_caida = 6500;
	this->teclado = teclado;
	this->calcular_tamannos();

	this->textura_sombra = recursos->obtener_textura(T_Sombra);
	this->textura_nota_blanca = recursos->obtener_textura(T_NotaBlanca);
	this->textura_nota_negra = recursos->obtener_textura(T_NotaNegra);
	//this->textura_sombra_nota = recursos->obtener_textura(T_SombraNota);

	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
	this->texto = recursos->obtener_tipografia(LetraMuyChica);
}

Tablero_Notas::~Tablero_Notas()
{
}

std::array<Color, 52> *Tablero_Notas::o_blancas_presionadas()
{
	return &this->teclas_activas_blancas;
}

std::array<Color, 36> *Tablero_Notas::o_negras_presionadas()
{
	return &this->teclas_activas_negras;
}

void Tablero_Notas::e_tiempo(microseconds_t tiempo)
{
	this->tiempo_actual_midi = tiempo;
}

void Tablero_Notas::e_notas(NotasPistas notas)
{
	this->notas = notas;
	for(int i=0; i<notas.size(); i++)
	{
		this->ultima_nota.push_back(0);//Se inician todas las pistas en 0
	}
}

void Tablero_Notas::e_lineas(MidiEventMicrosecondList lineas)
{
	this->lineas = lineas;
}

void Tablero_Notas::e_pistas(std::map<int, Pista*> *pistas)
{
	this->pistas = pistas;
}

void Tablero_Notas::e_dimension(int ancho, int alto)
{
	this->ancho = ancho;
	this->alto = alto;
	this->calcular_tamannos();
}

void Tablero_Notas::c_velocidad_caida(int valor)
{
	if(valor < 0)
		this->velocidad_caida = this->velocidad_caida - 100;
	else
		this->velocidad_caida = this->velocidad_caida + 100;

	if(this->velocidad_caida < 1500)
		this->velocidad_caida = 1500;
	else if(this->velocidad_caida > 14000)
		this->velocidad_caida = 14000;
}

void Tablero_Notas::c_teclado(Teclado *teclado)
{
	this->teclado = teclado;
	this->calcular_tamannos();
}

void Tablero_Notas::reiniciar()
{
	for(int i=0; i<this->ultima_nota.size(); i++)
	{
		this->ultima_nota[i] = 0;
	}
}

void Tablero_Notas::actualizar(unsigned int diferencia_tiempo)
{
}

void Tablero_Notas::dibujar()
{
	this->rectangulo->dibujar(this->x, this->y, this->ancho, this->alto, Color(0.95f, 0.95f, 0.95f), false);

	this->rectangulo->color(Color(0.7f, 0.7f, 0.7f));
	this->dibujar_lineas_horizontales();
	this->dibujar_lineas_verticales();

	this->rectangulo->textura(true);
	this->textura_sombra->activar();
	this->rectangulo->dibujar(this->x, this->y, this->ancho, 20);
/*
	for(int pista=0; pista<notas.size(); pista++)
	{
		if(notas[pista].size() > 0)
			this->dibujar_notas(pista, this->textura_sombra_nota, NULL);//Dibuja la sombra de la nota
	}
	//TODO ¿se podran dibujar las notas en un framebuffer diferente?
*/
	this->rectangulo->extremos_fijos(true);
	for(int pista=0; pista<notas.size(); pista++)
	{
		if(notas[pista].size() > 0)
			this->dibujar_notas(pista, this->textura_nota_blanca, this->textura_nota_negra);//Dibuja la nota
	}
	this->rectangulo->extremos_fijos(false);
}

void Tablero_Notas::evento_raton(Raton *raton)
{
}

void Tablero_Notas::calcular_tamannos()
{
	this->ancho_blanca = (this->ancho / this->teclado->o_numero_blancas());
	this->ancho_negra = this->ancho_blanca * PROPORCION_ANCHO_NEGRA;

	//Diferencia producida porque no se puede dibujar menos de un pixel
	this->ajuste_x = (this->ancho - (this->ancho_blanca * this->teclado->o_numero_blancas())) / 2;
}

void Tablero_Notas::dibujar_lineas_horizontales()
{
	int numero_linea = 0;
	int posicion_y = 0;

	for(int i=0; i<lineas.size(); i++)
	{
		numero_linea++;
		posicion_y = ((this->tiempo_actual_midi - lineas[i]) / this->velocidad_caida) + this->alto;
		if(posicion_y < 0)
			break;
		else if(posicion_y > this->alto)
			continue;

		this->rectangulo->dibujar(this->x, this->y+posicion_y, this->ancho, 1);
		this->texto->imprimir(this->x+10, this->y+posicion_y, std::to_string(numero_linea));
	}
}

void Tablero_Notas::dibujar_lineas_verticales()
{
	int posicion_x = this->ajuste_x + this->ancho_blanca * this->teclado->o_primera_barra();
	bool en_do = this->teclado->o_en_do_primera_barra();
	for(int i=0; i<15; i++)
	{
		if(posicion_x > this->ancho)
			break;

		this->rectangulo->dibujar(this->x+posicion_x, this->y, 1, this->alto);
		if(en_do)
			posicion_x += this->ancho_blanca * 3;
		else
			posicion_x += this->ancho_blanca * 4;
		en_do = !en_do;
	}
}

void Tablero_Notas::dibujar_notas(int pista, Textura2D *textura_nota_blanca, Textura2D *textura_nota_negra)
{
	int ajuste_negra = 0;
	int ancho_tecla = 0;
	int posicion_blanca = 0;
	int posicion_negra = 0;
	int largo_nota = 0;
	int largo_final = 0;
	int ajuste_y = 0;
	int posicion_y = 0;

	for(int n=this->ultima_nota[pista]; n<notas[pista].size(); n++)
	{
		posicion_y = (this->tiempo_actual_midi - notas[pista][n].start) / this->velocidad_caida;

		if(posicion_y < -this->alto)
			break;//No se dibujan las notas que aun no entran en la pantalla
		largo_nota = (notas[pista][n].end - notas[pista][n].start) / this->velocidad_caida;

		if(posicion_y-largo_nota > 0 && largo_nota >= 10 || posicion_y-10 > 0 && largo_nota < 10|| largo_nota == 0)//La nota n salio de la pantalla
		{
			if(n == this->ultima_nota[pista])
				this->ultima_nota[pista] = n+1;
			else if(n == this->ultima_nota[pista]+1)//Comprueba que la nota anterior haya terminado
			{
				int posicion_y_anterior = (this->tiempo_actual_midi - notas[pista][this->ultima_nota[pista]].start) / this->velocidad_caida;
				int largo_nota_anterior = (notas[pista][this->ultima_nota[pista]].end - notas[pista][this->ultima_nota[pista]].start) / this->velocidad_caida;
				if(posicion_y_anterior-largo_nota_anterior > 0)
				{
					this->ultima_nota[pista] = n+1;
				}
			}
			continue;//No se dibujan las notas que ya salieron de la pantalla o son invisibles (largo igual a cero)
		}

		posicion_blanca = Octava::prosicion_nota(notas[pista][n].note_id) - this->teclado->o_desplazamiento_blancas();

		//No dibuja las notas fuera de la pantalla hacia los lados
		if((this->ajuste_x + posicion_blanca * this->ancho_blanca) > this->ancho)
			continue;
		if(this->ajuste_x + posicion_blanca * this->ancho_blanca < 0)
			continue;

		if(Octava::es_negra(notas[pista][n].note_id))
		{
			ancho_tecla = this->ancho_negra;
			int negra = Octava::numero_negra(notas[pista][n].note_id);
			if(negra==1 || negra == 3)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.667);
			else if(negra==2 || negra == 5)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.333);
			else if(negra==4)
				ajuste_negra = this->ancho_blanca - (this->ancho_negra * 0.5);

			textura_nota_negra->activar();
			if(posicion_y >= 0)
			{
				posicion_negra = Octava::prosicion_nota_negra(notas[pista][n].note_id) - this->teclado->o_desplazamiento_negras();
				teclas_activas_negras[posicion_negra] = pistas->at(notas[pista][n].track_id)->o_color();
			}
		}
		else
		{
			ancho_tecla = this->ancho_blanca;
			ajuste_negra = 0;

			textura_nota_blanca->activar();
			if(posicion_y >= 0)
			{
				teclas_activas_blancas[posicion_blanca] = pistas->at(notas[pista][n].track_id)->o_color();
			}
		}

		//Recorta la parte de la nota que no se ve
		if(posicion_y > 20)
		{
			ajuste_y = posicion_y - 20;//Para compensar la posicion y de la nota
			largo_final = largo_nota - (posicion_y-20);//Reduce el alto de la nota
		}
		else
		{
			ajuste_y = 0;
			largo_final = largo_nota;
		}

		this->rectangulo->color(pistas->at(notas[pista][n].track_id)->o_color());
		this->rectangulo->dibujar_estirable(this->x+this->ajuste_x + posicion_blanca * this->ancho_blanca + ajuste_negra, this->y+this->alto + posicion_y-ajuste_y, ancho_tecla, largo_final, 5);
	}
}
