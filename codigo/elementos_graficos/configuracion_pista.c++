#include "configuracion_pista.h++"

Configuracion_Pista::Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto), m_datos_pista(pista), m_seleccion_modo(20, 85, 70, 55, recursos), m_seleccion_color(137, 85, 70, 55, recursos)
{
	m_rectangulo = recursos->obtener_figura(F_Rectangulo);

	m_texto_instrumento.texto(m_datos_pista.o_instrumento());
	m_texto_instrumento.tipografia(recursos->obtener_tipografia(LetraMediana));
	m_texto_instrumento.color(Color(1.0f, 1.0f, 1.0f));

	m_texto_notas.texto(std::to_string(m_datos_pista.o_numero_notas()) + " notas");
	m_texto_notas.tipografia(recursos->obtener_tipografia(LetraMuyChica));
	m_texto_notas.color(Color(1.0f, 1.0f, 1.0f));

	m_texto_sonido.tipografia(recursos->obtener_tipografia(LetraMuyChica));
	m_texto_sonido.color(Color(1.0f, 1.0f, 1.0f));
	m_texto_sonido.dimension(100, 8);
	m_texto_sonido.centrado(true);

	m_textura_fondo = recursos->obtener_textura(T_ConfiguracionPista);

	m_textura_reproducir = recursos->obtener_textura(T_Reproducir);
	m_textura_pausar = recursos->obtener_textura(T_Pausar);

	m_textura_sonido_activado = recursos->obtener_textura(T_SonidoActivado);
	m_textura_sonido_desactivado = recursos->obtener_textura(T_SonidoDesactivado);

	std::vector<std::string> opcion_modo;
	opcion_modo.push_back("Izquierza");
	opcion_modo.push_back("Mano Derecha");
	opcion_modo.push_back("Fondo");

	std::vector<std::string> opcion_color;
	opcion_color.push_back("Rojo");
	opcion_color.push_back("Verde");
	opcion_color.push_back("Azul");
	opcion_color.push_back("Morado");
	opcion_color.push_back("Rosado");

	std::vector<Textura2D*> icono_modos;
	icono_modos.push_back(recursos->obtener_textura(T_SonidoActivado));
	icono_modos.push_back(recursos->obtener_textura(T_SonidoDesactivado));
	icono_modos.push_back(recursos->obtener_textura(T_Reproducir));

	std::vector<Textura2D*> icono_color;
	icono_color.push_back(recursos->obtener_textura(T_ParticulaNota));
	icono_color.push_back(recursos->obtener_textura(T_SonidoDesactivado));
	icono_color.push_back(recursos->obtener_textura(T_SonidoActivado));
	icono_color.push_back(recursos->obtener_textura(T_Pausar));
	icono_color.push_back(recursos->obtener_textura(T_Reproducir));

	m_seleccion_modo.dimension_icono(40, 40);
	m_seleccion_modo.opciones_textos(opcion_modo);
	m_seleccion_modo.opciones_iconos(icono_modos);
	m_seleccion_modo.tipografia(recursos->obtener_tipografia(LetraMuyChica));
	m_seleccion_modo.opcion_predeterminada(0);

	m_seleccion_color.dimension_icono(40, 40);
	m_seleccion_color.opciones_textos(opcion_color);
	m_seleccion_color.opciones_iconos(icono_color);
	m_seleccion_color.tipografia(recursos->obtener_tipografia(LetraMuyChica));
	m_seleccion_color.opcion_predeterminada(0);

	m_vista_previa = new Boton(300, 22, 30, 30, "", recursos);
	m_vista_previa->color_boton(Color(1.0f, 1.0f, 1.0f));
	m_vista_previa->textura(m_textura_reproducir);

	m_boton_sonido = new Boton(272, 87, 40, 40, "", recursos);
	m_boton_sonido->color_boton(Color(1.0f, 1.0f, 1.0f));
	if(m_datos_pista.o_sonido())
	{
		m_boton_sonido->textura(m_textura_sonido_activado);
		m_texto_sonido.texto("Sonido activado");
	}
	else
	{
		m_boton_sonido->textura(m_textura_sonido_desactivado);
		m_texto_sonido.texto("Sin sonido");
	}

	m_estado_vista_previa = false;
}

Configuracion_Pista::~Configuracion_Pista()
{
	delete m_vista_previa;
	delete m_boton_sonido;
}

Pista Configuracion_Pista::o_pista()
{
	return m_datos_pista;
}

void Configuracion_Pista::actualizar(unsigned int diferencia_tiempo)
{
	m_seleccion_modo.actualizar(diferencia_tiempo);
	m_seleccion_color.actualizar(diferencia_tiempo);
	m_vista_previa->actualizar(diferencia_tiempo);
	m_boton_sonido->actualizar(diferencia_tiempo);

	m_seleccion_modo.ajuste(this->posicion_x(), this->posicion_y());
	m_seleccion_color.ajuste(this->posicion_x(), this->posicion_y());
	m_vista_previa->ajuste(this->posicion_x(), this->posicion_y());
	m_boton_sonido->ajuste(this->posicion_x(), this->posicion_y());

	m_texto_instrumento.posicion(this->posicion_x()+20, this->posicion_y()+15);
	m_texto_notas.posicion(this->posicion_x()+20, this->posicion_y()+35);
	m_texto_sonido.posicion(this->posicion_x()+242, this->posicion_y()+128);
}

void Configuracion_Pista::dibujar()
{
	m_rectangulo->textura(true);
	m_textura_fondo->activar();
	m_rectangulo->dibujar(this->posicion_x(), this->posicion_y(), this->ancho(), this->alto(), m_datos_pista.o_color());
	//m_rectangulo->dibujar(this->posicion_x(), this->posicion_y()+128, this->ancho(), 8, Color(0.8f, 0.2f, 0.7f)); //Para alinear el texto

	m_texto_instrumento.dibujar();
	m_texto_notas.dibujar();
	m_texto_sonido.dibujar();

	m_seleccion_modo.dibujar();
	m_seleccion_color.dibujar();
	m_vista_previa->dibujar();
	m_boton_sonido->dibujar();
}

void Configuracion_Pista::evento_raton(Raton *raton)
{
	m_seleccion_modo.evento_raton(raton);
	m_seleccion_color.evento_raton(raton);
	m_vista_previa->evento_raton(raton);
	m_boton_sonido->evento_raton(raton);

	if(m_vista_previa->esta_activado())
	{
		m_estado_vista_previa = !m_estado_vista_previa;
		if(m_estado_vista_previa)
			m_vista_previa->textura(m_textura_pausar);
		else
			m_vista_previa->textura(m_textura_reproducir);
	}

	if(m_boton_sonido->esta_activado())
	{

		bool estado = m_datos_pista.o_sonido();
		estado = !estado;
		m_datos_pista.e_sonido(estado);
		if(estado)
		{
			m_texto_sonido.texto("Sonido activado");
			m_boton_sonido->textura(m_textura_sonido_activado);
		}
		else
		{
			m_texto_sonido.texto("Sin sonido");
			m_boton_sonido->textura(m_textura_sonido_desactivado);
		}
	}
}

void Configuracion_Pista::evento_pantalla(int ancho, int alto)
{
}
