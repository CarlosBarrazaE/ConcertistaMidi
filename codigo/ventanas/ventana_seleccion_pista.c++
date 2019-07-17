#include "ventana_seleccion_pista.h++"

VentanaSeleccionPista::VentanaSeleccionPista(Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana()
{
	this->musica = musica;

	Textura2D *textura = recursos->obtener_textura(T_Boton);
	Color color(0.9f, 0.9f, 0.9f);

	boton_atras = new Boton(10, Pantalla::alto - 32, 120, 25, "Atrás", textura, color, false, recursos);
	boton_continuar = new Boton(Pantalla::ancho - 130, Pantalla::alto - 32, 120, 25, "Continuar", textura, color, false, recursos);

	Texto *texto_boton = recursos->obtener_tipografia(LetraChica);
	boton_atras->e_letra(texto_boton);
	boton_continuar->e_letra(texto_boton);

	rectangulo = recursos->obtener_figura(F_Rectangulo);
	texto = recursos->obtener_tipografia(LetraTitulo);
	ajuste_titulo = texto->ancho_texto("Selección de Pistas") / 2;

	barra_desplazamiento = new Barra_Desplazamiento(0, 40, Pantalla::ancho, Pantalla::alto - 80, 350, 150, 10, 10, recursos);

	if(this->musica->o_pistas()->size() > 0)
		this->cargar_configuracion(recursos);
	else
		this->crear_configuracion(recursos);
}

VentanaSeleccionPista::~VentanaSeleccionPista()
{
	delete boton_atras;
	delete boton_continuar;
}

void VentanaSeleccionPista::crear_configuracion(Administrador_Recursos *recursos)
{
	int numero_pistas = this->musica->o_musica()->Notes().size();
	std::vector<Pista> pistas;

	int color_usado = 0;
	Configuracion_Pista *configuracion;
	Color color_pista;
	bool visible = true;
	for(int i=0; i<numero_pistas; i++)
	{
		MidiTrack pista_actual = this->musica->o_musica()->Tracks()[i];
		if(pista_actual.Notes().size() > 0)
		{
			if(pista_actual.IsPercussion())
			{
				color_pista = Color(0.5f, 0.5f, 0.5f);
				visible = false;
			}
			else
			{
				color_pista = Pista::colores_pista[color_usado % NUMERO_COLORES_PISTA];
				visible = true;
				color_usado++;
			}

			configuracion = new Configuracion_Pista(0, 0, 350, 150, Pista(pista_actual.InstrumentName(), pista_actual.Notes().size(), color_pista, Fondo, visible, true), recursos);
			configuracion_pistas.push_back(configuracion);
			barra_desplazamiento->agregar_elemento(configuracion);
			pistas.push_back(Pista(pista_actual.InstrumentName(), pista_actual.Notes().size(), color_pista, Fondo, visible, true));
		}
	}

	this->musica->e_pistas(pistas);
}

void VentanaSeleccionPista::cargar_configuracion(Administrador_Recursos *recursos)
{
	std::vector<Pista> *pistas = this->musica->o_pistas();
	Configuracion_Pista *configuracion;
	for(int i=0; i<pistas->size(); i++)
	{
		configuracion = new Configuracion_Pista(0, 0, 350, 150, pistas->at(i), recursos);
		configuracion_pistas.push_back(configuracion);
		barra_desplazamiento->agregar_elemento(configuracion);
	}
}

void VentanaSeleccionPista::guardar_configuracion()
{
	std::vector<Pista> pistas;

	int pistas_validas = 0;
	for(int i=0; i<configuracion_pistas.size(); i++)
	{
		pistas.push_back(configuracion_pistas[i]->o_pista());
	}
	this->musica->e_pistas(pistas);
}

void VentanaSeleccionPista::actualizar(unsigned int diferencia_tiempo)
{
	this->boton_atras->actualizar(diferencia_tiempo);
	this->boton_continuar->actualizar(diferencia_tiempo);
	this->barra_desplazamiento->actualizar(diferencia_tiempo);
}

void VentanaSeleccionPista::dibujar()
{
	this->barra_desplazamiento->dibujar();
	this->rectangulo->textura(false);
	this->rectangulo->dibujar(0, 0, Pantalla::ancho, 40, Color(0.141f, 0.624f, 0.933f));
	this->rectangulo->dibujar(0, Pantalla::alto - 40, Pantalla::ancho, 40, Color(0.761f, 0.887f, 0.985f));
	this->texto->imprimir(Pantalla::centro_h() - ajuste_titulo, 30, "Selección de Pistas", Color(1.0f, 1.0f, 1.0f));

	this->boton_atras->dibujar();
	this->boton_continuar->dibujar();
}

void VentanaSeleccionPista::evento_raton(Raton *raton)
{
	this->boton_atras->evento_raton(raton);
	this->boton_continuar->evento_raton(raton);
	this->barra_desplazamiento->evento_raton(raton);

	if(boton_atras->esta_activado())
		this->accion = CambiarASeleccionMusica;

	if(boton_continuar->esta_activado())
		this->accion = CambiarAOrgano;
}

void VentanaSeleccionPista::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
		this->accion = CambiarASeleccionMusica;
	else if(tecla == TECLA_ENTRAR && !estado)
	{
		this->accion = CambiarAOrgano;
		this->guardar_configuracion();
	}
}

void VentanaSeleccionPista::evento_pantalla(int ancho, int alto)
{
	this->barra_desplazamiento->c_dimension(ancho, alto-80);
	this->boton_atras->posicion_y(alto - 32);

	this->boton_continuar->posicion_x(ancho - 130);
	this->boton_continuar->posicion_y(alto - 32);
}
