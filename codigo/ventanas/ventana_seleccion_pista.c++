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

	NotasPistas np = this->musica->o_musica()->Notes();
	int numero_pistas = np.size();

	std::vector<Pista> pistas;

	int x=50;
	int y=100;
	int color_udado = 0;
	for(int i=0; i<numero_pistas; i++)
	{
		MidiTrack pista_actual = this->musica->o_musica()->Tracks()[i];
		Modo modo;
		Color color_pista;
		if(pista_actual.Notes().size() > 0)
		{
			if(pista_actual.IsPercussion())
			{
				color_pista = Color(0.5f, 0.5f, 0.5f);
				modo = AutomaticoOculto;
			}
			else
			{
				color_pista = Pista::colores_pista[color_udado % NUMERO_COLORES_PISTA];
				modo = Automatico;
				color_udado++;
			}

			Configuracion_Pista c = Configuracion_Pista(x, y, pista_actual.InstrumentName(), pista_actual.Notes().size(), Pista(color_pista, modo), recursos);
			configuracion_pistas.push_back(c);
			x += c.o_ancho() + 10;
			if(x+c.o_ancho() > 1600)
			{
				x = 50;
				y += c.o_alto() + 10;
			}
		}
		else
		{
			color_pista = Color(0.5f, 0.5f, 0.5f);
			modo = NoTocar;
		}
		pistas.push_back(Pista(color_pista, modo));
	}

	this->musica->e_pistas(pistas);
}

VentanaSeleccionPista::~VentanaSeleccionPista()
{
	delete boton_atras;
	delete boton_continuar;
}

void VentanaSeleccionPista::actualizar(unsigned int diferencia_tiempo)
{
	this->boton_atras->actualizar(diferencia_tiempo);
	this->boton_continuar->actualizar(diferencia_tiempo);
	for(int i=0; i<this->configuracion_pistas.size(); i++)
		this->configuracion_pistas[i].actualizar(diferencia_tiempo);
}

void VentanaSeleccionPista::dibujar()
{
	this->rectangulo->textura(false);
	this->rectangulo->dibujar(0, 0, Pantalla::ancho, 40, Color(0.141f, 0.624f, 0.933f));
	this->rectangulo->dibujar(0, Pantalla::alto - 40, Pantalla::ancho, 40, Color(0.761f, 0.887f, 0.985f));
	this->texto->imprimir(Pantalla::centro_h() - ajuste_titulo, 30, "Selección de Pistas", Color(1.0f, 1.0f, 1.0f));

	this->boton_atras->dibujar();
	this->boton_continuar->dibujar();

	for(int i=0; i<this->configuracion_pistas.size(); i++)
		this->configuracion_pistas[i].dibujar();
}

void VentanaSeleccionPista::evento_raton(Raton *raton)
{
	this->boton_atras->evento_raton(raton);
	this->boton_continuar->evento_raton(raton);

	for(int i=0; i<this->configuracion_pistas.size(); i++)
		this->configuracion_pistas[i].evento_raton(raton);

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
		this->accion = CambiarAOrgano;
}

void VentanaSeleccionPista::evento_pantalla(int ancho, int alto)
{
	this->boton_atras->posicion_y(alto - 32);

	this->boton_continuar->posicion_x(ancho - 130);
	this->boton_continuar->posicion_y(alto - 32);
}
