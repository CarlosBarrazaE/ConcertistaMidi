#include "tablero_notas.h++"

Tablero_Notas::Tablero_Notas(int x, int y, int ancho, int alto, Teclado_Configuracion *teclado, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	m_velocidad_caida = 6500;
	m_teclado = teclado;
	this->calcular_tamannos();

	m_textura_sombra = recursos->obtener_textura(T_Sombra);
	m_textura_nota = recursos->obtener_textura(T_Nota);

	m_rectangulo = recursos->obtener_figura(F_Rectangulo);
	m_tipografia = recursos->obtener_tipografia(LetraMuyChica);
	m_recursos = recursos;

	for(int i=0; i<52; i++)
	{
		m_tiempo_espera_blancas[i] = 0;
		if(i<36)
			m_tiempo_espera_negras[i] = 0;
	}
}

Tablero_Notas::~Tablero_Notas()
{
	for(std::map<int, Etiqueta*>::iterator i = m_texto_numeros.begin(); i != m_texto_numeros.end(); i++)
		delete i->second;
	m_texto_numeros.clear();
}

std::array<Color, 52> *Tablero_Notas::o_blancas_presionadas()
{
	return &m_teclas_activas_blancas;
}

std::array<Color, 36> *Tablero_Notas::o_negras_presionadas()
{
	return &m_teclas_activas_negras;
}

void Tablero_Notas::e_tiempo(microseconds_t tiempo)
{
	m_tiempo_actual_midi = tiempo;
}

void Tablero_Notas::e_notas(NotasPistas notas)
{
	m_notas = notas;
	for(int i=0; i<notas.size(); i++)
	{
		m_ultima_nota.push_back(0);//Se inician todas las pistas en 0
	}
}

void Tablero_Notas::e_lineas(MidiEventMicrosecondList lineas)
{
	m_lineas = lineas;
}

void Tablero_Notas::e_pistas(std::vector<Pista> *pistas)
{
	m_pistas = pistas;
}

void Tablero_Notas::e_dimension(int ancho, int alto)
{
	this->ancho(ancho);
	this->alto(alto);
	this->calcular_tamannos();
}

void Tablero_Notas::c_velocidad_caida(int valor)
{
	if(valor < 0)
		m_velocidad_caida = m_velocidad_caida - 100;
	else
		m_velocidad_caida = m_velocidad_caida + 100;

	if(m_velocidad_caida < 1500)
		m_velocidad_caida = 1500;
	else if(m_velocidad_caida > 14000)
		m_velocidad_caida = 14000;
}

void Tablero_Notas::c_teclado(Teclado_Configuracion *teclado)
{
	m_teclado = teclado;
	this->calcular_tamannos();
}

void Tablero_Notas::reiniciar()
{
	for(int i=0; i<m_ultima_nota.size(); i++)
	{
		m_ultima_nota[i] = 0;
	}
	for(int i=0; i<52; i++)
	{
		m_tiempo_espera_blancas[i] = 0;
		if(i<36)
			m_tiempo_espera_negras[i] = 0;
	}
}

void Tablero_Notas::actualizar(unsigned int diferencia_tiempo)
{
	for(int i=0; i<52; i++)
	{
		if(m_tiempo_espera_blancas[i] > 0)
		{
			m_tiempo_espera_blancas[i] -= 1;
		}
		if(i<36)
		{
			if(m_tiempo_espera_negras[i] > 0)
			{
				m_tiempo_espera_negras[i] -= 1;
			}
		}
	}
}

void Tablero_Notas::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y(), this->ancho(), this->alto(), Color(0.95f, 0.95f, 0.95f));

	m_rectangulo->color(Color(0.7f, 0.7f, 0.7f));
	this->dibujar_lineas_horizontales();
	this->dibujar_lineas_verticales();

	m_rectangulo->textura(true);
	m_textura_sombra->activar();
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y(), this->ancho(), 20);

	m_rectangulo->extremos_fijos(false, true);
	for(int pista=0; pista<m_notas.size(); pista++)
	{
		if(m_notas[pista].size() > 0)
		{
			if(m_pistas->at(pista).o_visible())
				this->dibujar_notas(pista);//Dibuja la nota
		}
	}
	m_rectangulo->extremos_fijos(false, false);
}

void Tablero_Notas::evento_raton(Raton *raton)
{
}

void Tablero_Notas::evento_pantalla(int ancho, int alto)
{
}

void Tablero_Notas::calcular_tamannos()
{
	m_ancho_blanca = (this->ancho() / m_teclado->o_numero_blancas());
	m_ancho_negra = m_ancho_blanca * PROPORCION_ANCHO_NEGRA;

	//Diferencia producida porque no se puede dibujar menos de un pixel
	m_ajuste_x = (this->ancho() - (m_ancho_blanca * m_teclado->o_numero_blancas())) / 2;
}

void Tablero_Notas::dibujar_lineas_horizontales()
{
	int numero_linea = 0;
	int posicion_y = 0;
	Etiqueta *numero_temporal;

	for(int i=0; i<m_lineas.size(); i++)
	{
		numero_linea++;
		posicion_y = ((m_tiempo_actual_midi - m_lineas[i]) / m_velocidad_caida) + this->alto();
		if(posicion_y < 0)
			break;
		else if(posicion_y > this->alto())
			continue;
		numero_temporal = m_texto_numeros[numero_linea];
		if(!numero_temporal)
		{
			numero_temporal = new Etiqueta(this->posicion_x()+10, this->posicion_y()+posicion_y, false, std::to_string(numero_linea), m_tipografia, m_recursos);
			m_texto_numeros[numero_linea] = numero_temporal;
		}

		m_rectangulo->dibujar(this->posicion_x(), this->posicion_y()+posicion_y, this->ancho(), 1);
		
		numero_temporal->posicion_x(this->posicion_x()+10);
		numero_temporal->posicion_y(this->posicion_y()+posicion_y-m_tipografia->alto_texto());
		numero_temporal->dibujar();
	}
}

void Tablero_Notas::dibujar_lineas_verticales()
{
	int posicion_x = m_ajuste_x + m_ancho_blanca * m_teclado->o_primera_barra();
	bool en_do = m_teclado->o_en_do_primera_barra();
	for(int i=0; i<15; i++)
	{
		if(posicion_x > this->ancho())
			break;

		m_rectangulo->dibujar(this->posicion_x()+posicion_x, this->posicion_y(), 1, this->alto());
		if(en_do)
			posicion_x += m_ancho_blanca * 3;
		else
			posicion_x += m_ancho_blanca * 4;
		en_do = !en_do;
	}
}

void Tablero_Notas::dibujar_notas(int pista)
{
	int ajuste_negra = 0;
	int ancho_tecla = 0;
	int posicion_blanca = 0;
	int posicion_negra = 0;
	int largo_nota = 0;
	int largo_final_nota = 0;
	int posicion_y = 0;//Es negativo hasta que la tota sale de la pantalla
	bool es_negra = false;

	for(int n=m_ultima_nota[pista]; n<m_notas[pista].size(); n++)
	{
		posicion_y = (m_tiempo_actual_midi - m_notas[pista][n].start) / m_velocidad_caida;
		if(posicion_y < -this->alto())
		{
			break;//No se dibujan las notas que aun no entran en la pantalla
		}
		largo_nota = (m_notas[pista][n].end - m_notas[pista][n].start) / m_velocidad_caida;

		//Alto minimo de la nota a mostrar = 20
		if(posicion_y-largo_nota > 0 && largo_nota >= 20 || posicion_y-20 > 0 && largo_nota < 20 || largo_nota == 0)//La nota n salio de la pantalla
		{
			if(n == m_ultima_nota[pista])
				m_ultima_nota[pista] = n+1;
			else if(n == m_ultima_nota[pista]+1)//Comprueba que la nota anterior haya terminado
			{
				int posicion_y_anterior = (m_tiempo_actual_midi - m_notas[pista][m_ultima_nota[pista]].start) / m_velocidad_caida;
				int largo_nota_anterior = (m_notas[pista][m_ultima_nota[pista]].end - m_notas[pista][m_ultima_nota[pista]].start) / m_velocidad_caida;
				if(posicion_y_anterior-largo_nota_anterior > 0)
				{
					m_ultima_nota[pista] = n+1;
				}
			}
			continue;//No se dibujan las notas que ya salieron de la pantalla o son invisibles (largo igual a cero)
		}

		posicion_blanca = Octava::prosicion_nota(m_notas[pista][n].note_id) - m_teclado->o_desplazamiento_blancas();

		//No dibuja las notas fuera de la pantalla hacia los lados
		if((m_ajuste_x + posicion_blanca * m_ancho_blanca) > this->ancho())
			continue;
		if(m_ajuste_x + posicion_blanca * m_ancho_blanca < 0)
			continue;

		if(Octava::es_negra(m_notas[pista][n].note_id))
		{
			ancho_tecla = m_ancho_negra;
			int negra = Octava::numero_negra(m_notas[pista][n].note_id);
			if(negra==1 || negra == 3)
				ajuste_negra = m_ancho_blanca - (m_ancho_negra * 0.667);
			else if(negra==2 || negra == 5)
				ajuste_negra = m_ancho_blanca - (m_ancho_negra * 0.333);
			else if(negra==4)
				ajuste_negra = m_ancho_blanca - (m_ancho_negra * 0.5);

			if(posicion_y >= -5 && posicion_y < 0 && m_tiempo_espera_negras[posicion_blanca] == 0)
			{
				posicion_negra = Octava::prosicion_nota_negra(m_notas[pista][n].note_id) - m_teclado->o_desplazamiento_negras();
				m_tiempo_espera_negras[posicion_negra] = (-posicion_y)-1;
			}
			else if(posicion_y >= 0)
			{
			//if(posicion_y >= 0)//Nuevo
			//{//Nuevo
				posicion_negra = Octava::prosicion_nota_negra(m_notas[pista][n].note_id) - m_teclado->o_desplazamiento_negras();
				if(m_tiempo_espera_negras[posicion_negra] <= 0)
				{
					m_teclas_activas_negras[posicion_negra] = m_pistas->at(pista).o_color();
				}
			}
			//}//Nuevo
			es_negra = true;
		}
		else
		{
			ancho_tecla = m_ancho_blanca;
			ajuste_negra = 0;

			if(posicion_y >= -5 && posicion_y < 0 && m_tiempo_espera_blancas[posicion_blanca] == 0)
			{
				m_tiempo_espera_blancas[posicion_blanca] = (-posicion_y)-1;
			}
			else if(posicion_y >= 0)
			{
				if(m_tiempo_espera_blancas[posicion_blanca] <= 0)
				{
				//if(posicion_y >= 0)//Nuevo
					m_teclas_activas_blancas[posicion_blanca] = m_pistas->at(pista).o_color();
				}
			}
			es_negra = false;
		}

		//Recorta la parte de la nota que no se ve
		if(posicion_y > 20)
			largo_final_nota = largo_nota - (posicion_y-20);//Reduce el alto de la nota
		else
			largo_final_nota = largo_nota;

		//20 es le alto minimo alto de la nota, es la suma de los 2 bordes fijos
		if(largo_final_nota < 20)
		{
			largo_nota += 20 - largo_final_nota;
			largo_final_nota = 20;
		}

		if(es_negra)
			m_rectangulo->color(m_pistas->at(pista).o_color()-0.3);
		else
			m_rectangulo->color(m_pistas->at(pista).o_color());
		m_textura_nota->activar();
		m_rectangulo->dibujar_estirable(this->posicion_x()+m_ajuste_x + posicion_blanca * m_ancho_blanca + ajuste_negra, this->posicion_y()+this->alto()+posicion_y-largo_nota, ancho_tecla, largo_final_nota, 0, 10);
	}
}
