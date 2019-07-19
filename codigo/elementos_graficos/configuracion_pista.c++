#include "configuracion_pista.h++"

Configuracion_Pista::Configuracion_Pista(int x, int y, int ancho, int alto, Pista pista, Administrador_Recursos *recursos)
: Elemento(x, y, ancho, alto), datos_pista(pista)
{
	this->rectangulo = recursos->obtener_figura(F_Rectangulo);
	this->texto = recursos->obtener_tipografia(LetraMediana);
	this->texto_chico = recursos->obtener_tipografia(LetraMuyChica);
	this->textura_fondo = recursos->obtener_textura(T_ConfiguracionPista);

	this->textura_reproducir = recursos->obtener_textura(T_Reproducir);
	this->textura_pausar = recursos->obtener_textura(T_Pausar);

	this->textura_sonido_activado = recursos->obtener_textura(T_SonidoActivado);
	this->textura_sonido_desactivado = recursos->obtener_textura(T_SonidoDesactivado);

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

	this->seleccion_modo = new Lista_Desplegable(20, 85, 77, 55, 40, 40, true, opcion_modo, icono_modos, this->texto_chico, recursos);
	this->seleccion_color = new Lista_Desplegable(137, 85, 77, 55, 40, 40, true, opcion_color, icono_color, this->texto_chico, recursos);

	this->vista_previa = new Boton(300, 22, 30, 30, "", textura_reproducir, Color(1.0f, 1.0f, 1.0f), false, recursos);

	Textura2D *textura_sonido_actual;
	if(this->datos_pista.o_sonido())
	{
		textura_sonido_actual = textura_sonido_activado;
		this->texto_sonido = "Sonido activado";
	}
	else
	{
		textura_sonido_actual = textura_sonido_desactivado;
		this->texto_sonido = "Sin sonido";
	}

	this->boton_sonido = new Boton(272, 87, 40, 40, "", textura_sonido_actual, Color(1.0f, 1.0f, 1.0f), false, recursos);
	this->centro_texto_sonido = this->texto_chico->ancho_texto(texto_sonido) / 2;

	this->estado_vista_previa = false;
}

Configuracion_Pista::~Configuracion_Pista()
{
	delete seleccion_modo;
	delete seleccion_color;
	delete vista_previa;
	delete boton_sonido;
}

Pista Configuracion_Pista::o_pista()
{
	return this->datos_pista;
}

void Configuracion_Pista::actualizar(unsigned int diferencia_tiempo)
{
	seleccion_modo->actualizar(diferencia_tiempo);
	seleccion_color->actualizar(diferencia_tiempo);
	vista_previa->actualizar(diferencia_tiempo);
	boton_sonido->actualizar(diferencia_tiempo);

	seleccion_modo->ajuste(this->x, this->y);
	seleccion_color->ajuste(this->x, this->y);
	vista_previa->ajuste(this->x, this->y);
	boton_sonido->ajuste(this->x, this->y);
}

void Configuracion_Pista::dibujar()
{
	this->rectangulo->textura(true);
	this->textura_fondo->activar();
	this->rectangulo->dibujar(this->x, this->y, this->ancho, this->alto, this->datos_pista.o_color());
	this->texto->imprimir(this->x+20, this->y+40, this->datos_pista.o_instrumento(), Color(1.0f, 1.0f, 1.0f));
	this->texto_chico->imprimir(this->x+20, this->y+55, std::to_string(this->datos_pista.o_numero_notas()) + " notas", Color(1.0f, 1.0f, 1.0f));
	this->texto_chico->imprimir(this->x+292 - centro_texto_sonido, this->y+137, this->texto_sonido, Color(1.0f, 1.0f, 1.0f));
	seleccion_modo->dibujar();
	seleccion_color->dibujar();
	vista_previa->dibujar();
	boton_sonido->dibujar();
}

void Configuracion_Pista::evento_raton(Raton *raton)
{
	seleccion_modo->evento_raton(raton);
	seleccion_color->evento_raton(raton);
	vista_previa->evento_raton(raton);
	boton_sonido->evento_raton(raton);

	if(vista_previa->esta_activado())
	{
		estado_vista_previa = !estado_vista_previa;
		if(estado_vista_previa)
			vista_previa->e_textura(textura_pausar);
		else
			vista_previa->e_textura(textura_reproducir);
	}

	if(boton_sonido->esta_activado())
	{

		bool estado = this->datos_pista.o_sonido();
		estado = !estado;
		this->datos_pista.e_sonido(estado);
		if(estado)
		{
			this->texto_sonido = "Sonido activado";
			this->boton_sonido->e_textura(textura_sonido_activado);
		}
		else
		{
			this->texto_sonido = "Sin sonido";
			this->boton_sonido->e_textura(textura_sonido_desactivado);
		}

		this->centro_texto_sonido = this->texto_chico->ancho_texto(texto_sonido) / 2;
	}
}
