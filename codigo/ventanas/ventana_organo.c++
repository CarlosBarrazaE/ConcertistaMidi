#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	rectangulo = recursos->obtener_figura(F_Rectangulo);

	//musica = new Midi(Midi::ReadFromFile("../musica/Ven Señor no tardes propia.midi"));
	musica = new Midi(Midi::ReadFromFile("../musica/Banjo Kazooie -  Opening.midi"));
	//musica = new Midi(Midi::ReadFromFile("../musica/Escala_musícal.midi"));
	musica->Reset(5500000, 1000000);
	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();

	Teclado *teclado = Tipo_Teclado::obtener_teclado(Teclas88);

	barra = new Barra_Progreso(0, 40, Pantalla::ancho, 40, musica->GetSongLengthInMicroseconds(), musica->GetBarLines(), recursos);
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, teclado, recursos);
	tablero = new Tablero_Notas(0, barra->o_alto()+40, Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto() + 40), teclado, recursos);

	this->velocidad_musica = 1.0;
	this->texto_titulo = recursos->obtener_tipografia(LetraTitulo);
	this->texto = recursos->obtener_tipografia(LetraChica);

	Registro::aviso("Dispositivos de entrada:");
	for(int x=0; x<dispositivos_entrada.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_entrada[x].name);
	}

	Registro::aviso("Dispositivos de salida:");
	for(int x=0; x<dispositivos_salida.size(); x++)
	{
		Registro::aviso("\tNombre: " + dispositivos_salida[x].name);
	}

	midi_entrada = new MidiCommIn(3);//Deberia seleccionarse el id del dispositivo (Teclado)
	midi_salida = new MidiCommOut(1);//Deberia seleccionarse el id del dispositivo (Timidity 0)

	pistas[0] = new Pista(Color(0.0f, 0.598f, 0.0f), Automatico);//Verde
	pistas[1] = new Pista(Color(0.0f, 0.598f, 1.0f), Automatico);//Azul
	pistas[2] = new Pista(Color(1.0f, 0.598f, 1.0f), Automatico);//Rosado
	pistas[3] = new Pista(Color(1.0f, 0.424f, 0.0f), Automatico);//Salmon
	pistas[4] = new Pista(Color(1.0f, 0.0f, 0.467f), Automatico);
	pistas[5] = new Pista(Color(0.587f, 0.0f, 0.467f), Automatico);
	pistas[6] = new Pista(Color(0.261f, 0.0f, 0.467f), Automatico);
	pistas[7] = new Pista(Color(0.0f, 0.0f, 0.467f), Automatico);
	pistas[8] = new Pista(Color(0.0f, 0.761f, 0.467f), Automatico);
	pistas[9] = new Pista(Color(0.0f, 0.761f, 1.0f), Automatico);
	pistas[10] = new Pista(Color(1.0f, 0.761f, 0.609f), Automatico);
	pistas[11] = new Pista(Color(1.0f, 0.761f, 0.0f), Automatico);
	pistas[12] = new Pista(Color(0.489f, 0.587f, 0.489f), Automatico);
	pistas[13] = new Pista(Color(0.489f, 0.0f, 0.489f), Automatico);
	pistas[14] = new Pista(Color(1.0f, 0.0f, 0.489f), Automatico);
	pistas[15] = new Pista(Color(0.407f, 0.348f, 0.408f), Automatico);
	pistas[16] = new Pista(Color(0.407f, 0.348f, 0.0f), Automatico);
	pistas[17] = new Pista(Color(0.407f, 0.348f, 1.0f), Automatico);
	pistas[18] = new Pista(Color(0.0f, 0.348f, 1.0f), Automatico);
	pistas[19] = new Pista(Color(0.0f, 0.348f, 0.0f), Automatico);

	tablero->e_notas(musica->Notes());
	tablero->e_pistas(&pistas);
	tablero->e_lineas(musica->GetBarLines());
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
	midi_salida->Reset();
	delete barra;
	delete tablero;
	delete organo;
	delete musica;
	delete midi_entrada;
	delete midi_salida;
}

void VentanaOrgano::actualizar(unsigned int diferencia_tiempo)
{
	if(musica->IsSongOver())
	{
		this->accion = CambiarASeleccionPista;
	}
	unsigned int microsegundos_actualizar = (diferencia_tiempo / 1000.0) * velocidad_musica;

	if(this->pausa)
		microsegundos_actualizar = 0;

	MidiEventListWithTrackId evs = musica->Update(microsegundos_actualizar);

	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); i++)
	{
		midi_salida->Write(i->second);
		if(this->texto_evento.size() < 100)
			this->texto_evento += i->second.Text();
		else
			this->texto_evento = i->second.Text();
	}

	if(barra->o_tiempo_seleccionado() > 0)
	{
		musica->GoTo(barra->o_tiempo_seleccionado());
		tablero->reiniciar();
		midi_salida->Reset();
	}

	barra->actualizar(diferencia_tiempo);
	tablero->actualizar(diferencia_tiempo);
	organo->actualizar(diferencia_tiempo);

	barra->e_tiempo(musica->GetSongPositionInMicroseconds());
	tablero->e_tiempo(musica->GetSongPositionInMicroseconds());

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
	this->texto->imprimir(10, 100, this->texto_evento, Color(0.0f, 0.0f, 0.0f));
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
		this->accion = CambiarASeleccionPista;
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
			midi_salida->Reset();
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
	organo->e_y(alto);
	organo->e_ancho(ancho);
	tablero->e_dimension(ancho, alto - (organo->o_alto() + barra->o_alto()+40));
}
