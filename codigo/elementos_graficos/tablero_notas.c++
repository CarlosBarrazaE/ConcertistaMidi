#include "tablero_notas.h++"

Tablero_Notas::Tablero_Notas(float x, float y, float ancho, float alto, Teclado_Organo *teclado, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto)
{
	m_duracion_nota = 6500;
	m_teclado = teclado;
	this->calcular_tamannos();

	m_textura_sombra = recursos->textura(T_Sombra);
	m_textura_nota = recursos->textura(T_Nota);
	m_textura_nota_resaltada = recursos->textura(T_NotaResaltada);

	m_rectangulo = recursos->figura(F_Rectangulo);
	m_tipografia = recursos->tipografia(LetraMuyChica);
	m_recursos = recursos;

	for(unsigned int i=0; i<128; i++)
		m_tiempo_espera[i] = 0;
}

Tablero_Notas::~Tablero_Notas()
{
	for(std::map<int, Etiqueta*>::iterator i = m_texto_numeros.begin(); i != m_texto_numeros.end(); i++)
		delete i->second;
	m_texto_numeros.clear();
}

void Tablero_Notas::calcular_tamannos()
{
	m_ancho_blanca = (this->ancho() / static_cast<float>(Octava::numero_blancas(m_teclado->tecla_inicial(), m_teclado->numero_teclas())));
	m_ancho_negra = m_ancho_blanca * PROPORCION_ANCHO_NEGRA;
}

void Tablero_Notas::dibujar_lineas_horizontales()
{
	int numero_linea = 0;
	float posicion_y = 0;
	Etiqueta *numero_temporal;

	for(unsigned int i=0; i<m_lineas.size(); i++)
	{
		numero_linea++;

		//Dibuja solo las lineas que seran visibles
		posicion_y = ((static_cast<float>(m_tiempo_actual_midi) - static_cast<float>(m_lineas[i])) / static_cast<float>(m_duracion_nota)) + this->alto();
		if(posicion_y < 0)
			break;
		else if(posicion_y > this->alto())
			continue;

		//Se carga el numero de linea a mostrar
		numero_temporal = m_texto_numeros[numero_linea];
		if(!numero_temporal)
		{
			//Si no existe se crea
			numero_temporal = new Etiqueta(this->x()+10, this->y()+posicion_y, false, std::to_string(numero_linea), m_tipografia, m_recursos);
			m_texto_numeros[numero_linea] = numero_temporal;
		}

		//Dibuja la linea horizontal
		m_rectangulo->dibujar(this->x(), this->y()+posicion_y, this->ancho(), 1);

		//Dibuja el numero de linea
		numero_temporal->posicion(this->x()+10, this->y()+posicion_y-static_cast<float>(m_tipografia->alto_texto()));
		numero_temporal->dibujar();
	}
}

void Tablero_Notas::dibujar_lineas_verticales()
{
	float posicion_x = 0;
	bool primera_parte = false;//La primera parte corresponde a la linea de DO
	unsigned int posicion_inicial = m_teclado->tecla_inicial() % 12;
	if(posicion_inicial == 0 || posicion_inicial > 5)
	{
		//Dibuja linea de DO
		primera_parte = true;
		//Ajusta la posicion_x si no empieza en DO
		if(posicion_inicial != 0)
			posicion_x = m_ancho_blanca * static_cast<float>(8 - Octava::blancas_desde_inicio(posicion_inicial-1) - 1);
	}
	else
	{
		//Dibuja linea de FA
		//Ajusta la posicion_x si no empieza en FA
		if(posicion_inicial != 5)
			posicion_x = m_ancho_blanca * static_cast<float>(4 - Octava::blancas_desde_inicio(posicion_inicial-1) - 1);
	}
	for(int i=0; i<22 && posicion_x < this->ancho(); i++)
	{
		//Se dibuja la linea vertical
		m_rectangulo->dibujar(this->x()+posicion_x, this->y(), 1, this->alto());
		if(primera_parte)
			posicion_x += m_ancho_blanca * 3;
		else
			posicion_x += m_ancho_blanca * 4;
		primera_parte = !primera_parte;
	}
}

void Tablero_Notas::dibujar_notas(unsigned int pista)
{
	float largo_nota = 0;
	float largo_final_nota = 0;
	float posicion_y = 0;//Es negativo hasta que la tota sale de la pantalla

	//Datos para el dibujo final
	unsigned int numero_nota = 0;//Id de la nota desde 0 hasta 127
	unsigned int numero_notas_omitir = 0;
	if(m_teclado->tecla_inicial() > 0)
		numero_notas_omitir = Octava::blancas_desde_inicio(m_teclado->tecla_inicial()-1);
	float ancho_tecla = 0;//El ancho puede cambiar si es blanca o es negra
	float ajuste_negra = 0;//Permite desplazar la nota negra un poco en relacion a la blanca
	for(unsigned int n=m_ultima_nota[pista]; n<m_notas[pista].size(); n++)
	{
		//Numero_nota incluye blancas y negras
		numero_nota = m_notas[pista][n].note_id;

		//Se salta las notas fuera de la pantalla
		if(numero_nota < m_teclado->tecla_inicial() || numero_nota >= m_teclado->tecla_inicial() + m_teclado->numero_teclas())
			continue;

		posicion_y = static_cast<float>(m_tiempo_actual_midi - m_notas[pista][n].start) / static_cast<float>(m_duracion_nota);

		//No se dibujan las notas que aun no entran en la pantalla
		if(posicion_y < -this->alto())
			break;

		largo_nota = static_cast<float>(m_notas[pista][n].end - m_notas[pista][n].start) / static_cast<float>(m_duracion_nota);

		//El alto minimo de la nota a mostrar es de 20 pixeles
		if((posicion_y-largo_nota > 0 && largo_nota >= 20) || (posicion_y > 20 && largo_nota < 20) || largo_nota <= 0)//La nota n salio de la pantalla
		{
			if(n == m_ultima_nota[pista])
				m_ultima_nota[pista] = n+1;
			else if(n == m_ultima_nota[pista]+1)//Comprueba que la nota anterior haya terminado
			{
				float posicion_y_anterior = static_cast<float>(m_tiempo_actual_midi - m_notas[pista][m_ultima_nota[pista]].start) / static_cast<float>(m_duracion_nota);
				float largo_nota_anterior = static_cast<float>(m_notas[pista][m_ultima_nota[pista]].end - m_notas[pista][m_ultima_nota[pista]].start) / static_cast<float>(m_duracion_nota);
				if(posicion_y_anterior-largo_nota_anterior > 0)
				{
					m_ultima_nota[pista] = n+1;
				}
			}
			//No se dibujan las notas que ya salieron de la pantalla o son invisibles (largo igual a cero)
			continue;
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

		//Actualiza el tiempo de espera de las notas
		if(posicion_y >= -5 && posicion_y < 0 && m_tiempo_espera[numero_nota] <= 0)
			m_tiempo_espera[numero_nota] = (-posicion_y)-1;
		else if(posicion_y >= 0)
		{
			if(m_tiempo_espera[numero_nota] <= 0)
				m_teclas_activas[numero_nota] = m_pistas->at(pista).color();
		}

		if(Octava::es_blanca(m_notas[pista][n].note_id))
		{
			//Dibuja las notas blancas
			ancho_tecla = m_ancho_blanca;
			ajuste_negra = 0;

			//Se establece el color de la nota
			m_rectangulo->color(m_pistas->at(pista).color());
		}
		else
		{
			//Dibuja las notas negras
			ancho_tecla = m_ancho_negra;

			//Mueve la tecla un poco dependiendo de su posicion
			ajuste_negra = m_ancho_blanca + m_ancho_negra * Octava::desplazamiento_negra(numero_nota);

			//La nota negra es un poco mas oscura
			m_rectangulo->color(m_pistas->at(pista).color()-0.3f);
		}

		unsigned int numero_blancas = Octava::blancas_desde_inicio(numero_nota) - numero_notas_omitir;
		if(numero_blancas > 0)
			numero_blancas--;
		else
			ajuste_negra -= m_ancho_blanca;//Esto ocurre cuando comienza con una negra, se le quita el ancho de la blanca

		m_textura_nota->activar();
		m_rectangulo->dibujar_estirable(this->x() + static_cast<float>(numero_blancas) * m_ancho_blanca + ajuste_negra, this->y()+this->alto()+posicion_y-largo_nota, ancho_tecla, largo_final_nota, 0, 10);

		//Agrega una segunda textura a la nota tocada
		if(posicion_y > 0)
		{
			m_textura_nota_resaltada->activar();
			m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			m_rectangulo->dibujar_estirable(this->x() + static_cast<float>(numero_blancas) * m_ancho_blanca + ajuste_negra, this->y()+this->alto()+posicion_y-largo_nota, ancho_tecla, largo_final_nota, 0, 10);
		}
	}
}

void Tablero_Notas::actualizar(unsigned int diferencia_tiempo)
{
	float tiempo = static_cast<float>(diferencia_tiempo)/1000000000.0f*(1.0f/0.0166f);
	for(unsigned int i=0; i<128; i++)
	{
		if(m_tiempo_espera[i] > 0)
			m_tiempo_espera[i] -= tiempo;
	}
}

void Tablero_Notas::dibujar()
{
	//Dibuja el fondo
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), this->alto(), Color(0.95f, 0.95f, 0.95f));

	//Dibuja las lineas
	m_rectangulo->color(Color(0.7f, 0.7f, 0.7f));
	this->dibujar_lineas_horizontales();
	this->dibujar_lineas_verticales();

	//Dibuja las notas por pistas
	m_rectangulo->textura(true);
	m_rectangulo->extremos_fijos(false, true);
	for(unsigned int pista=0; pista<m_notas.size(); pista++)
	{
		//Dibuja solo las pistas que tienen notas, hay pistas vacias
		if(m_notas[pista].size() > 0)
		{
			//Dibuja solo las pistas visibles
			if(m_pistas->at(pista).visible())
				this->dibujar_notas(pista);
		}
	}
	m_rectangulo->extremos_fijos(false, false);

	//Dibuja la sombra de la barra de progreso
	m_textura_sombra->activar();
	m_rectangulo->color(Color(0.7f, 0.7f, 0.7f));
	m_rectangulo->dibujar(this->x(), this->y(), this->ancho(), 20);
}

void Tablero_Notas::evento_raton(Raton */*raton*/)
{
}

void Tablero_Notas::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
	this->calcular_tamannos();
}

std::array<Color, 128> *Tablero_Notas::estado_teclas()
{
	return &m_teclas_activas;
}

void Tablero_Notas::tiempo(microseconds_t tiempo)
{
	m_tiempo_actual_midi = tiempo;
}

void Tablero_Notas::notas(NotasPistas notas)
{
	m_notas = notas;
	for(unsigned int i=0; i<notas.size(); i++)
		m_ultima_nota.push_back(0);//Se inician todas las pistas en 0
}

void Tablero_Notas::lineas(MidiEventMicrosecondList lineas)
{
	m_lineas = lineas;
}

void Tablero_Notas::pistas(std::vector<Pista> *pistas)
{
	m_pistas = pistas;
}

int Tablero_Notas::duracion_nota()
{
	return m_duracion_nota;
}

void Tablero_Notas::duracion_nota(int valor)
{
	if(valor < 0)
		m_duracion_nota = m_duracion_nota - 100;
	else
		m_duracion_nota = m_duracion_nota + 100;

	if(m_duracion_nota < 1500)
		m_duracion_nota = 1500;
	else if(m_duracion_nota > 14000)
		m_duracion_nota = 14000;
}

void Tablero_Notas::modificar_duracion_nota(int valor)
{
	m_duracion_nota = valor;

	if(m_duracion_nota < 1500)
		m_duracion_nota = 1500;
	else if(m_duracion_nota > 14000)
		m_duracion_nota = 14000;
}

void Tablero_Notas::reiniciar()
{
	for(unsigned int i=0; i<m_ultima_nota.size(); i++)
		m_ultima_nota[i] = 0;
	for(unsigned int i=0; i<128; i++)
		m_tiempo_espera[i] = 0;
}
