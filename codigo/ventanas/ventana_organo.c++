#include "ventana_organo.h++"

VentanaOrgano::VentanaOrgano(Administrador_Recursos *recursos) : Ventana()
{
	organo = new Organo(0, Pantalla::alto, Pantalla::ancho, Teclas88, recursos);
	musica = new Midi(Midi::ReadFromFile("/home/carlos/Música/Midis/Celular/Navidad_Jingle_Bells_1.midi"));
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

	midi_entrada = new MidiCommIn(3);
	midi_salida = new MidiCommOut(1);

	const microseconds_t PreviewLeadIn  = 0;
	const microseconds_t PreviewLeadOut = 0;
	musica->Reset(PreviewLeadIn, PreviewLeadOut);
}

VentanaOrgano::~VentanaOrgano()
{

}

void VentanaOrgano::actualizar(Raton *raton)
{
	MidiEventListWithTrackId evs = musica->Update(Fps::obtener_nanosegundos() / 1000.0);//1.000.000 microsegundos = 1 segundo, dividido en 60 fps

	for (MidiEventListWithTrackId::const_iterator i = evs.begin(); i != evs.end(); ++i)
	{
		midi_salida->Write(i->second);
	}

	organo->actualizar_y(Pantalla::alto);
	organo->actualizar_ancho(Pantalla::ancho);
	organo->actualizar(raton);
}

void VentanaOrgano::dibujar()
{
	organo->dibujar();
}
