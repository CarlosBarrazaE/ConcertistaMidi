#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Configuracion *configuracion, Datos_Musica *musica, Administrador_Recursos *recursos) : Ventana()
{
	this->configuracion = configuracion;
	this->musica = musica;

	rectangulo = recursos->obtener_figura(F_Rectangulo);
	Teclado *teclado = Tipo_Teclado::obtener_teclado(Teclas88);

	barra = new Barra_Progreso(0, 40, Pantalla::ancho, 40, musica->o_musica()->GetSongLengthInMicroseconds(), musica->o_musica()->GetBarLines(), recursos);
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, teclado, recursos);
	tablero = new Tablero_Notas(0, barra->o_alto()+40, Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto() + 40), teclado, recursos);

	this->velocidad_musica = 1.0;
	this->texto_titulo = recursos->obtener_tipografia(LetraTitulo);
	this->texto = recursos->obtener_tipografia(LetraChica);

	tablero->e_notas(musica->o_musica()->Notes());
	tablero->e_pistas(musica->o_pistas());
	tablero->e_lineas(musica->o_musica()->GetBarLines());
	organo->e_blancas_presionadas(tablero->o_blancas_presionadas());
	organo->e_negras_presionadas(tablero->o_negras_presionadas());
	this->cambio_velocidad = false;
	this->ancho_titulo = this->texto_titulo->ancho_texto("100%") / 2;
	this->pausa = false;
	this->texto_pausa = "Pausa";
	this->ancho_pausa = this->texto_titulo->ancho_texto(this->texto_pausa) / 2;
}

VentanaOrgano::~VentanaOrgano()
{
	delete barra;
	delete tablero;
	delete organo;
}

void VentanaOrgano::actualizar(unsigned int diferencia_tiempo)
{
	if(musica->o_musica()->IsSongOver())
	{
		this->musica->reiniciar();
		this->accion = CambiarASeleccionPista;
	}
	unsigned int microsegundos_actualizar = (diferencia_tiempo / 1000.0) * velocidad_musica;

	if(this->pausa)
		microsegundos_actualizar = 0;

	MidiEventListWithTrackId evs = musica->o_musica()->Update(microsegundos_actualizar);

	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); i++)
	{
		configuracion->o_salida()->Write(i->second);
	}

	if(barra->o_tiempo_seleccionado() > 0)
	{
		musica->o_musica()->GoTo(barra->o_tiempo_seleccionado());
		tablero->reiniciar();
		configuracion->o_salida()->Reset();
	}

	barra->actualizar(diferencia_tiempo);
	tablero->actualizar(diferencia_tiempo);
	organo->actualizar(diferencia_tiempo);

	barra->e_tiempo(musica->o_musica()->GetSongPositionInMicroseconds());
	tablero->e_tiempo(musica->o_musica()->GetSongPositionInMicroseconds());

	if(this->cambio_velocidad)
	{
		this->cambio_velocidad = false;
		this->ancho_titulo = this->texto_titulo->ancho_texto(std::to_string((int)(velocidad_musica*100)) + "%") / 2;
	}
}

void VentanaOrgano::dibujar()
{
	tablero->dibujar();
	barra->dibujar();
	organo->dibujar();
	rectangulo->textura(false);
	rectangulo->dibujar(0, 0, Pantalla::ancho, 40, Color(0.141f, 0.624f, 0.933f));
	this->texto_titulo->imprimir(Pantalla::centro_h() - this->ancho_titulo, 30, std::to_string((int)(velocidad_musica*100)) + "%", Color(1.0f, 1.0f, 1.0f));
	if(this->pausa)
		this->texto_titulo->imprimir(Pantalla::centro_h() - this->ancho_titulo, 200, this->texto_pausa, Color(0.0f, 0.0f, 0.0f));
}

void VentanaOrgano::evento_raton(Raton *raton)
{
	barra->evento_raton(raton);
	tablero->evento_raton(raton);
	organo->evento_raton(raton);
}

void VentanaOrgano::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_ESCAPE && !estado)
	{
		configuracion->o_salida()->Reset();
		this->musica->reiniciar();
		this->accion = CambiarASeleccionPista;
	}
	else if(tecla == TECLA_FLECHA_ARRIBA && estado)
		tablero->c_velocidad_caida(1);
	else if(tecla == TECLA_FLECHA_ABAJO && estado)
		tablero->c_velocidad_caida(-1);
	else if(tecla == TECLA_FLECHA_IZQUIERDA && estado)
	{
		velocidad_musica-=0.01;
		if(velocidad_musica < 0.01)
			velocidad_musica = 0.01;
		this->cambio_velocidad = true;
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		velocidad_musica+=0.01;
		if(velocidad_musica > 2)
			velocidad_musica = 2;
		this->cambio_velocidad = true;
	}
	else if(tecla == TECLA_ESPACIO && !estado)
	{
		this->pausa = !this->pausa;
		if(this->pausa)
			configuracion->o_salida()->Reset();
	}
	else if(tecla == TECLA_F5 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()+40));
	}
	else if(tecla == TECLA_F6 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()+40));
	}
	else if(tecla == TECLA_F7 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()+40));
	}
	else if(tecla == TECLA_F8 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()+40));
	}
	else if(tecla == TECLA_F9 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()+40));
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	barra->e_ancho(ancho);
	organo->posicion_y(alto);
	organo->e_ancho(ancho);
	tablero->e_dimension(ancho, alto - (organo->o_alto() + barra->o_alto()+40));
}
