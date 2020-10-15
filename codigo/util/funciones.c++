#include "funciones.h++"

namespace Funciones
{
	std::string microsegundo_a_texto(microseconds_t ms, bool mostrar_vacio)
	{
		int seg  = static_cast<int>(ms / 1000000);
		int horas = seg / 3600;
		int minutos = (seg - (horas * 3600)) / 60;
		int segundos =  (seg - (horas * 3600 + minutos * 60));

		std::string tminutos, tsegundos;
		if(minutos < 10)
			tminutos = "0" + std::to_string(minutos);
		else
			tminutos = std::to_string(minutos);

		if(segundos < 10)
			tsegundos = "0" + std::to_string(segundos);
		else
			tsegundos = std::to_string(segundos);

		if(!mostrar_vacio && horas == 0)
			return tminutos + ":" + tsegundos;
		else
			return std::to_string(horas) + ":" + tminutos + ":" + tsegundos;
	}

	microseconds_t duracion_midi(std::string ruta_midi)
	{
		Midi *archivo_midi = NULL;
		try
		{
			archivo_midi = new Midi(Midi::ReadFromFile(ruta_midi));
		}
		catch(const MidiError &e)
		{
			Registro::Error("No se puede abrir el archivo MIDI " + e.GetErrorDescription());
			archivo_midi = NULL;
		}
		if(archivo_midi != NULL)
		{
			microseconds_t duracion = archivo_midi->GetSongLengthInMicroseconds();//Tiempo en segundos leer midi
			delete archivo_midi;
			return duracion;
		}
		return 0;
	}

	bool comparar_float(float valor1, float valor2, float diferencia_minima)
	{
		if(valor1 < valor2 + diferencia_minima && valor1 > valor2 - diferencia_minima)
			return true;
		return false;
	}
}
