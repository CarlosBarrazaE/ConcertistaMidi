#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	//musica = new Midi(Midi::ReadFromFile("../musica/Ven Señor no tardes propia.midi"));
	musica = new Midi(Midi::ReadFromFile("../musica/Click Clock Wood - Sax Quartet.midi"));
	//musica = new Midi(Midi::ReadFromFile("../musica/Escala_musícal.midi"));
	musica->Reset(3000000, 3000000);
	MidiCommDescriptionList dispositivos_entrada = MidiCommIn::GetDeviceList();
	MidiCommDescriptionList dispositivos_salida = MidiCommOut::GetDeviceList();

	Teclado *teclado = Tipo_Teclado::obtener_teclado(Teclas88);

	barra = new Barra_Progreso(0, 0, Pantalla::ancho, 40, musica->GetSongLengthInMicroseconds(), musica->GetBarLines(), recursos);
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, teclado, recursos);
	tablero = new Tablero_Notas(0, barra->o_alto(), Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()), teclado, recursos);

	this->velocidad_musica = 1.0;
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

	pistas[0] = new Pista(Color(0.0f, 0.598f, 0.0f), Automatico);
	pistas[1] = new Pista(Color(0.0f, 0.598f, 1.0f), Automatico);
	pistas[2] = new Pista(Color(1.0f, 0.598f, 1.0f), Automatico);
	pistas[3] = new Pista(Color(1.0f, 0.424f, 0.0f), Automatico);
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
}

VentanaOrgano::~VentanaOrgano()
{
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
		musica->Reset(3000000, 3000000);
		tablero->reiniciar();
	}
	MidiEventListWithTrackId evs = musica->Update((diferencia_tiempo / 1000.0) * velocidad_musica);

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
	}

	barra->actualizar(diferencia_tiempo);
	tablero->actualizar(diferencia_tiempo);
	organo->actualizar(diferencia_tiempo);

	barra->e_tiempo(musica->GetSongPositionInMicroseconds());
	tablero->e_tiempo(musica->GetSongPositionInMicroseconds());
}

void VentanaOrgano::dibujar()
{
	tablero->dibujar();
	barra->dibujar();
	organo->dibujar();
	this->texto->imprimir(10, 80, "Velocidad: " + std::to_string((int)(velocidad_musica*100)) + "%", Color(0.0f, 0.0f, 0.0f));
	this->texto->imprimir(10, 100, this->texto_evento, Color(0.0f, 0.0f, 0.0f));
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
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		velocidad_musica+=0.01;
		if(velocidad_musica > 2)
			velocidad_musica = 2;
	}
	else if(tecla == TECLA_F5 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas37));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F6 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas49));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F7 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas61));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F8 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas76));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
	else if(tecla == TECLA_F9 && estado)
	{
		tablero->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		organo->c_teclado(Tipo_Teclado::obtener_teclado(Teclas88));
		tablero->e_dimension(Pantalla::ancho, Pantalla::alto - (organo->o_alto() + barra->o_alto()));
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	barra->e_ancho(ancho);
	organo->e_y(alto);
	organo->e_ancho(ancho);
	tablero->e_dimension(ancho, alto - (organo->o_alto() + barra->o_alto()));
}
