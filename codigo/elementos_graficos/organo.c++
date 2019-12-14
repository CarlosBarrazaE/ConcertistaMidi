#include "organo.h++"

Organo::Organo(int x, int y, int ancho, Teclado_Configuracion *teclado, Administrador_Recursos *recursos) : Elemento(x, y, ancho, 0)
{
	//El origen del organo esta abajo a la izquierda
	m_teclado = teclado;
	calcular_tamannos();

	m_tecla_blanca = recursos->obtener_textura(T_TeclaBlanca);
	m_tecla_negra = recursos->obtener_textura(T_TeclaNegra);

	m_tecla_blanca_presionada = recursos->obtener_textura(T_TeclaBlancaPresionada);
	m_tecla_blanca_presionada_doble = recursos->obtener_textura(T_TeclaBlancaPresionadaDoble);
	m_tecla_negra_presionada = recursos->obtener_textura(T_TeclaNegraPresionada);

	m_borde_negro = recursos->obtener_textura(T_BordeOrganoNegro);
	m_borde_rojo = recursos->obtener_textura(T_BordeOrganoRojo);

	m_rectangulo = recursos->obtener_figura(F_Rectangulo);

	Sombreador *particulas = recursos->obtener_sombreador(S_Particula);
	Textura2D *t_particula = recursos->obtener_textura(T_ParticulaNota);
	m_generador_particulas = new Generador_Particulas(particulas, t_particula, 500, m_ancho_tecla_blanca);
}

Organo::~Organo()
{
}

void Organo::calcular_tamannos()
{
	m_ancho_tecla_blanca = (this->ancho() / m_teclado->o_numero_blancas());
	m_alto_tecla_blanca = m_ancho_tecla_blanca * PROPORCION_BLANCA;
	if(m_alto_tecla_blanca > 250)
		m_alto_tecla_blanca = 250;

	m_ancho_tecla_negra = m_ancho_tecla_blanca * PROPORCION_ANCHO_NEGRA;
	m_alto_tecla_negra = m_alto_tecla_blanca * PROPORCION_NEGRA;

	this->alto(m_alto_tecla_blanca + 11);

	//Diferencia producida porque no se puede dibujar menos de un pixel
	m_ancho_real = m_ancho_tecla_blanca * m_teclado->o_numero_blancas();
	m_ajuste_x = (this->ancho() - m_ancho_real) / 2;
}

void Organo::ancho(int valor)
{
	m_ancho = valor;
	this->calcular_tamannos();
	m_generador_particulas->e_escala(m_ancho_tecla_blanca);
}

int Organo::ancho()
{
	return m_ancho;
}

void Organo::c_teclado(Teclado_Configuracion *teclado)
{
	m_teclado = teclado;
	this->calcular_tamannos();
	m_generador_particulas->e_escala(m_ancho_tecla_blanca);
}

void Organo::e_blancas_presionadas(std::array<Color, 52> *teclas_blancas)
{
	m_teclas_activas_blancas = teclas_blancas;
}

void Organo::e_negras_presionadas(std::array<Color, 36> *teclas_negras)
{
	m_teclas_activas_negras = teclas_negras;
}

void Organo::actualizar(unsigned int diferencia_tiempo)
{
	m_generador_particulas->actualizar(((double)diferencia_tiempo/1000000000.0)*3);
}

void Organo::dibujar()
{
	m_rectangulo->textura(false);
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y() - this->alto(), this->ancho(), this->alto(), Color(0.0f, 0.0f, 0.0f));

	m_tecla_blanca->activar();
	m_rectangulo->textura(true);
	m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	this->dibujar_blancas(this->posicion_x() + this->m_ajuste_x, this->posicion_y() - this->alto() + 10, m_teclado->o_numero_blancas());

	m_tecla_negra->activar();
	this->dibujar_negras(this->posicion_x() + this->m_ajuste_x, this->posicion_y() - this->alto() + 10, m_teclado->o_numero_negras());

	m_borde_negro->activar();
	m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y() - this->alto(), this->ancho(), 5);

	m_borde_rojo->activar();
	m_rectangulo->dibujar(this->posicion_x() + this->m_ajuste_x, this->posicion_y() - this->alto() + 5, m_ancho_real-1, 5);

	m_generador_particulas->dibujar();
}

void Organo::evento_raton(Raton *raton)
{
}

void Organo::evento_pantalla(int ancho, int alto)
{
}

void Organo::dibujar_blancas(int x, int y, int numero_teclas)
{
	int desplazamiento = x;
	Color negro;
	bool tecla_presionada_anterior = false;
	for(int n=0; n<numero_teclas; n++)
	{
		if(m_teclas_activas_blancas->at(n) != negro)
		{
			m_rectangulo->color(m_teclas_activas_blancas->at(n));
			m_generador_particulas->agregar_particulas(desplazamiento + m_ancho_tecla_blanca/2.0 - m_ancho_tecla_blanca/2, y, 2, m_teclas_activas_blancas->at(n));
			m_teclas_activas_blancas->at(n) = negro;
			if(tecla_presionada_anterior)
				m_tecla_blanca_presionada_doble->activar();
			else
				m_tecla_blanca_presionada->activar();
			tecla_presionada_anterior = true;
		}
		else
		{
			m_tecla_blanca->activar();
			m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			tecla_presionada_anterior = false;
		}

		m_rectangulo->dibujar(desplazamiento, y, m_ancho_tecla_blanca - 1, m_alto_tecla_blanca);
		desplazamiento += m_ancho_tecla_blanca;
	}
}

void Organo::dibujar_negras(int x, int y, int numero_teclas)
{
	int desplazamiento = 0;
	int n_blanca = m_teclado->o_inicio_blancas();
	int n_negra = m_teclado->o_inicio_negras();
	Color negro;
	Color color_actual;
	bool tecla_activa = false;
	for(int n=0; n<numero_teclas; n++)
	{
		if(m_teclas_activas_negras->at(n) != negro)
		{
			m_rectangulo->color(m_teclas_activas_negras->at(n));
			color_actual = m_teclas_activas_negras->at(n);
			m_teclas_activas_negras->at(n) = negro;
			m_tecla_negra_presionada->activar();
			tecla_activa = true;
		}
		else
		{
			m_rectangulo->color(Color(1.0f, 1.0f, 1.0f));
			m_tecla_negra->activar();
			tecla_activa = false;
		}
		if(n_negra==0 || n_negra == 2)
		{
			n_blanca++;
			desplazamiento = x + n_blanca * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.667;
		}
		else if(n_negra==1 || n_negra == 4)
			desplazamiento = x + n_blanca * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.333;
		else if(n_negra==3)
			desplazamiento = x + n_blanca * m_ancho_tecla_blanca - m_ancho_tecla_negra * 0.5;

		n_negra++;
		n_blanca++;
		if(n_negra == 5)
			n_negra = 0;

		if(tecla_activa)
			m_generador_particulas->agregar_particulas(desplazamiento + m_ancho_tecla_negra/2.0 - m_ancho_tecla_blanca/2, y, 2, color_actual-0.2f);
		//El ancho de la tecla mas el ancho de la sombra
		m_rectangulo->dibujar(desplazamiento, y, m_ancho_tecla_negra + m_ancho_tecla_negra * 0.22, m_alto_tecla_negra);
	}
}
