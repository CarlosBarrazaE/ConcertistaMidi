#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, Teclas88, recursos);
	tablero = new Tablero_Notas(0, 0, Pantalla::ancho, Pantalla::alto - organo->o_alto(), recursos);
	tablero->e_ajuste_x(organo->o_ajuste_x());
	tablero->e_ancho_blanca(organo->o_ancho_blancas());
	tablero->e_ancho_negra(organo->o_ancho_negras());
	this->velocidad_musica = 1.0;
	this->texto = recursos->obtener_tipografia(LetraChica);

	//musica = new Midi(Midi::ReadFromFile("../musica/Ven Señor no tardes propia.midi"));
	musica = new Midi(Midi::ReadFromFile("../musica/Banjo Kazooie -  Treasure Trove Cove.midi"));
	//musica = new Midi(Midi::ReadFromFile("../musica/Escala_musícal.midi"));
	dispositivos_entrada = MidiCommIn::GetDeviceList();
	dispositivos_salida = MidiCommOut::GetDeviceList();

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

	const microseconds_t PreviewLeadIn  = 0;
	const microseconds_t PreviewLeadOut = 0;
	musica->Reset(PreviewLeadIn, PreviewLeadOut);

	notas = musica->Notes();
	tablero->e_notas(notas);
}

VentanaOrgano::~VentanaOrgano()
{
	delete tablero;
	delete organo;
	delete musica;
}

void VentanaOrgano::actualizar(Raton *raton)
{
	MidiEventListWithTrackId evs = musica->Update((Fps::obtener_nanosegundos() / 1000.0) * velocidad_musica);

	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); ++i)
	{
		midi_salida->Write(i->second);
	}

	tablero->e_tiempo(musica->GetSongPositionInMicroseconds());//3250000

	organo->actualizar(raton);
	tablero->actualizar(raton);
}

void VentanaOrgano::dibujar()
{
	tablero->dibujar();
	organo->dibujar();
	this->texto->dibujar_texto(10, 40, "Velocidad: " + std::to_string((int)(velocidad_musica*100)) + "%", Color(0.0, 0.0, 0.0));
}

void VentanaOrgano::evento_teclado(Tecla tecla, bool estado)
{
	if(tecla == TECLA_FLECHA_ARRIBA && estado)
		tablero->c_velocidad_caida(1);
	else if(tecla == TECLA_FLECHA_ABAJO && estado)
		tablero->c_velocidad_caida(-1);
	else if(tecla == TECLA_FLECHA_IZQUIERDA && estado)
	{
		velocidad_musica-=0.01;
		if(velocidad_musica < 0.1)
			velocidad_musica = 0.1;
	}
	else if(tecla == TECLA_FLECHA_DERECHA && estado)
	{
		velocidad_musica+=0.01;
		if(velocidad_musica > 2)
			velocidad_musica = 2;
	}
}

void VentanaOrgano::evento_pantalla(int ancho, int alto)
{
	organo->e_y(Pantalla::alto);
	organo->e_ancho(Pantalla::ancho);

	tablero->e_ajuste_x(organo->o_ajuste_x());
	tablero->e_ancho_blanca(organo->o_ancho_blancas());
	tablero->e_ancho_negra(organo->o_ancho_negras());
	tablero->e_dimension(Pantalla::ancho, Pantalla::alto - organo->o_alto());
}
