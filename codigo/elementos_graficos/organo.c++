#include "organo.h++"

Organo::Organo(float x, float y, float ancho, Teclado_Configuracion *teclado, Administrador_Recursos *recursos) : Elemento(x, y, ancho, 0)
{
	//El origen del organo esta abajo a la izquierda
	m_teclado = teclado;
	calcular_tamannos();

	m_tecla_blanca = recursos->textura(T_TeclaBlanca);
	m_tecla_negra = recursos->textura(T_TeclaNegra);

	m_tecla_blanca_presionada = recursos->textura(T_TeclaBlancaPresionada);
	m_tecla_blanca_presionada_doble = recursos->textura(T_TeclaBlancaPresionadaDoble);
	m_tecla_negra_presionada = recursos->textura(T_TeclaNegraPresionada);

	m_borde_negro = recursos->textura(T_BordeOrganoNegro);
	m_borde_rojo = recursos->textura(T_BordeOrganoRojo);

	m_rectangulo = recursos->figura(F_Rectangulo);

	Sombreador *particulas = recursos->sombreador(S_Particula);
	Textura2D *t_particula = recursos->textura(T_ParticulaNota);
	m_generador_particulas = new Generador_Particulas(particulas, t_particula, 500, m_ancho_tecla_blanca);
	m_tiempo = 0;
	m_numero_particulas = 0;
}

Organo::~Organo()
{
}

void Organo::dibujar_blancas(float x, float y, unsigned int numero_teclas)
{
	float desplazamiento = x;
	Color negro;
	bool tecla_presionada_anterior = false;
	for(unsigned int n=0; n<numero_teclas; n++)
	{
		if(m_teclas_activas_blancas->at(n) != negro)
		{
			//La tecla es tocada y la tecla se cambia de color
			m_rectangulo->color(m_teclas_activas_blancas->at(n));

			//Se agregan las particulas del mismo color que la nota
			m_generador_particulas->agregar_particulas(desplazamiento + m_ancho_tecla_blanca/2.0f - m_ancho_tecla_blanca/2.0f, y, m_numero_particulas, m_teclas_activas_blancas->at(n));

			//Se borra el color porque ya se mostro
			m_teclas_activas_blancas->at(n) = negro;

			//Cambia el efectos de sombra
			if(tecla_presionada_anterior)
				m_tecla_blanca_presionada_doble->activar();
			else
				m_tecla_blanca_presionada->activar();
			tecla_presionada_anterior = true;
		}
		else
		{
			//La tecla no es tocada, color normal
			m_tecla_blanca->activar();
			m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			tecla_presionada_anterior = false;
		}

		m_rectangulo->dibujar(desplazamiento, y, m_ancho_tecla_blanca - 1, m_alto_tecla_blanca);
		desplazamiento += m_ancho_tecla_blanca;
	}
}

void Organo::dibujar_negras(float x, float y, unsigned int numero_teclas)
{
	int n_blanca = m_teclado->inicio_blancas();
	int n_negra = m_teclado->inicio_negras();
	float desplazamiento = 0;
	Color negro, color_actual;
	bool tecla_activa = false;
	for(unsigned int n=0; n<numero_teclas; n++)
	{
		if(m_teclas_activas_negras->at(n) != negro)
		{
			//La tecla es tocada y la tecla se cambia de color
			m_rectangulo->color(m_teclas_activas_negras->at(n));
			color_actual = m_teclas_activas_negras->at(n);

			//Se borra el color porque ya se mostro
			m_teclas_activas_negras->at(n) = negro;
			m_tecla_negra_presionada->activar();
			tecla_activa = true;
		}
		else
		{
			//La tecla no es tocada, color normal
			m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			m_tecla_negra->activar();
			tecla_activa = false;
		}
		if(n_negra==0 || n_negra == 2)
		{
			n_blanca++;
			desplazamiento = x + static_cast<float>(n_blanca) * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.667f;
		}
		else if(n_negra==1 || n_negra == 4)
			desplazamiento = x + static_cast<float>(n_blanca) * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.333f;
		else if(n_negra==3)
			desplazamiento = x + static_cast<float>(n_blanca) * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.5f;

		n_negra++;
		n_blanca++;
		if(n_negra == 5)
			n_negra = 0;

		//Se agregan las particulas del mismo color que la nota
		if(tecla_activa)
			m_generador_particulas->agregar_particulas(desplazamiento + m_ancho_tecla_negra/2.0f - m_ancho_tecla_blanca/2.0f, y, m_numero_particulas, color_actual-0.2f);

		//El ancho de la tecla mas el ancho de la sombra
		m_rectangulo->dibujar(desplazamiento, y, m_ancho_tecla_negra + m_ancho_tecla_negra * 0.22f, m_alto_tecla_negra);
	}
}

void Organo::calcular_tamannos()
{
	m_ancho_tecla_blanca = (this->ancho() / static_cast<float>(m_teclado->numero_blancas()));
	m_alto_tecla_blanca = m_ancho_tecla_blanca * PROPORCION_BLANCA;
	if(m_alto_tecla_blanca > 250)
		m_alto_tecla_blanca = 250;

	m_ancho_tecla_negra = m_ancho_tecla_blanca * PROPORCION_ANCHO_NEGRA;
	m_alto_tecla_negra = m_alto_tecla_blanca * PROPORCION_NEGRA;

	this->_dimension(this->ancho(), m_alto_tecla_blanca + 11);
}

void Organo::actualizar(unsigned int diferencia_tiempo)
{
	m_tiempo += static_cast<float>(diferencia_tiempo);

	//Generar particulas
	unsigned int particulas = static_cast<unsigned int>(m_tiempo / 16666666.0f);//16ms
	if(particulas > 0)
	{
		if(static_cast<float>(particulas) * 16666666 < m_tiempo)
			m_tiempo -= static_cast<float>(particulas * 16666666);
		m_numero_particulas = particulas*2;
	}
	else
		m_numero_particulas = 0;
	m_generador_particulas->actualizar((static_cast<float>(diferencia_tiempo)/1000000000.0f)*3.0f);
}

void Organo::dibujar()
{
	//Dibuja un fondo negro
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->x(), this->y() - this->alto(), this->ancho(), this->alto(), Color(0.0f, 0.0f, 0.0f));

	//Dibuja las notas blancas
	m_tecla_blanca->activar();
	m_rectangulo->textura(true);
	m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	this->dibujar_blancas(this->x(), this->y() - this->alto() + 10, m_teclado->numero_blancas());

	//Dibuja las notas negras
	m_tecla_negra->activar();
	this->dibujar_negras(this->x(), this->y() - this->alto() + 10, m_teclado->numero_negras());

	//Dibuja un borde negro
	m_borde_negro->activar();
	m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	m_rectangulo->dibujar(this->x(), this->y() - this->alto(), this->ancho(), 5);

	//Dibuja un borde rojo
	m_borde_rojo->activar();
	m_rectangulo->dibujar(this->x(), this->y() - this->alto() + 5, this->ancho(), 5);

	//Dibuja las particulas
	m_generador_particulas->dibujar();
}

void Organo::evento_raton(Raton */*raton*/)
{
}

void Organo::dimension(float ancho, float alto)
{
	this->_dimension(ancho, alto);
	this->calcular_tamannos();
	m_generador_particulas->escala(m_ancho_tecla_blanca);
}

void Organo::teclado(Teclado_Configuracion *teclado)
{
	m_teclado = teclado;
	this->calcular_tamannos();
	m_generador_particulas->escala(m_ancho_tecla_blanca);
}

void Organo::blancas_presionadas(std::array<Color, 52> *teclas_blancas)
{
	m_teclas_activas_blancas = teclas_blancas;
}

void Organo::negras_presionadas(std::array<Color, 36> *teclas_negras)
{
	m_teclas_activas_negras = teclas_negras;
}
