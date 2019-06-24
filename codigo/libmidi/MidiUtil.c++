// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include "MidiUtil.h"

MidiError::MidiError(MidiErrorCode error) : m_error(error)
{
}

unsigned long BigToSystem32(unsigned long x)
{
	return ntohl(x);
}

unsigned short BigToSystem16(unsigned short x)
{
	return ntohs(x);
}

unsigned long parse_variable_length(std::istream &in)
{
	register unsigned long value = in.get();

	if (in.good() && (value & 0x80))
	{
		value &= 0x7F;

		register unsigned long c;
		do
		{
			c = in.get();
			value = (value << 7) + (c & 0x7F);
		}
		while (in.good() && (c & 0x80));
	}

	return(value);
}

std::string MidiError::GetErrorDescription() const
{
	switch (m_error)
	{
		case MidiError_UnknownHeaderType:
			return "Se encontró un tipi de encabezado desconocido, es probable que no sea un archivo MIDI.";
		case MidiError_BadFilename:
			return "No se pudo abir el archivo de entrada, compruebe que el archivo existe";
		case MidiError_NoHeader:
			return "No se pudo leer ningún encavezado Midi, archivo muy corto.";
		case MidiError_BadHeaderSize:
			return "Tamaño incorrecto del encabezado.";
		case MidiError_Type2MidiNotSupported:
			return "MIDI tipo 2 no es compatible";
		case MidiError_BadType0Midi:
			return "El MIDI tipo 0 solo debe tener una pista";
		case MidiError_SMTPETimingNotImplemented:
			return "MIDI el uso de la división de tiempo SMTP no está implementada.";

		case MidiError_BadTrackHeaderType:
			return "Se encontró un tipo de encabezado de pista desconocido.";
		case MidiError_TrackHeaderTooShort:
			return "Archivo terminado antes de leer el encabezado de la pista.";
		case MidiError_TrackTooShort:
			return "Flijo de datos demasiado corto para leer la pista completa.";
		case MidiError_BadTrackEnd:
			return "La pista MIDI no terminó con el evento End-Of-Track (fin de pista).";

		case MidiError_EventTooShort:
			return "El flujo de datos finalizó antes del final del evento MIDI informado.";
		case MidiError_UnknownEventType:
			return "Se encontró un tipo de evento MIDI desconocido.";
		case MidiError_UnknownMetaEventType:
			return "Se encontró un tipo de evento de meta MIDI desconocido.";

		case MidiError_MM_NoDevice:
			return "No se pudo abrir el dispositivo MIDI espesificado.";
		case MidiError_MM_NotEnabled:
			return "El dispositivo MIDI no se pudo habilitar.";
		case MidiError_MM_AlreadyAllocated:
			return "El dispositivo MIDI espesificado ya está en uso.";
		case MidiError_MM_BadDeviceID:
			return "El ID del dispositivo MIDI espesificado está fuera de rango.";
		case MidiError_MM_InvalidParameter:
			return "Se usó un parárametro inválido con el dispositovo MIDI.";
		case MidiError_MM_NoDriver:
			return "El controlador MIDI espesificado no está instalado.";
		case MidiError_MM_NoMemory:
			return "No se puede asignar o bloquear la memoria para el dispositivo MIDI.";
		case MidiError_MM_Unknown:
			return "Se ha producido un error de E/S MIDI desconocido.";

		case MidiError_NoInputAvailable:
			return "Se intentó leer un evento MIDI desde un archivo de entrada vacío.";
		case MidiError_MetaEventOnInput:
			return "Un dispositivo de entrada MIDI envió un mata evento.";

		case MidiError_InputError:
			return "El controlador de entrada MIDI informó de un error.";
		case MidiError_InvalidInputErrorBehavior:
			return "Valor de InputError no válido. Las opciones son 'report', 'ignore', and 'use'";

		case MidiError_RequestedTempoFromNonTempoEvent:
			return "Los datos de tiempo se solicitaron desde un evento MIDI no temporal.";

		default:
			return "Codigo de error desconocido: " + std::to_string(m_error) + ".";
	}
}

std::string GetMidiEventTypeDescription(MidiEventType type)
{
	switch (type)
	{
		case MidiEventType_Meta:             return "Meta";
		case MidiEventType_SysEx:            return "System Exclusive";

		case MidiEventType_NoteOff:          return "Note-Off";
		case MidiEventType_NoteOn:           return "Note-On";
		case MidiEventType_Aftertouch:       return "Aftertouch";
		case MidiEventType_Controller:       return "Controller";
		case MidiEventType_ProgramChange:    return "Program Change";
		case MidiEventType_ChannelPressure:  return "Channel Pressure";
		case MidiEventType_PitchWheel:       return "Pitch Wheel";

		case MidiEventType_Unknown:          return "Unknown";
		default:                             return "BAD EVENT TYPE";
	}
}

std::string GetMidiMetaEventTypeDescription(MidiMetaEventType type)
{
  switch (type)
  {
	case MidiMetaEvent_SequenceNumber:   return "Sequence Number";

	case MidiMetaEvent_Text:             return "Text";
	case MidiMetaEvent_Copyright:        return "Copyright";
	case MidiMetaEvent_TrackName:        return "Track Name";
	case MidiMetaEvent_Instrument:       return "Instrument";
	case MidiMetaEvent_Lyric:            return "Lyric";
	case MidiMetaEvent_Marker:           return "Marker";
	case MidiMetaEvent_Cue:              return "Cue Point";
	case MidiMetaEvent_PatchName:        return "Patch Name";
	case MidiMetaEvent_DeviceName:       return "Device Name";

	case MidiMetaEvent_EndOfTrack:       return "End Of Track";
	case MidiMetaEvent_TempoChange:      return "Tempo Change";
	case MidiMetaEvent_SMPTEOffset:      return "SMPTE Offset";
	case MidiMetaEvent_TimeSignature:    return "Time Signature";
	case MidiMetaEvent_KeySignature:     return "Key Signature";

	case MidiMetaEvent_Proprietary:      return "Proprietary";

	case MidiMetaEvent_ChannelPrefix:    return "(Deprecated) Channel Prefix";
	case MidiMetaEvent_MidiPort:         return "(Deprecated) MIDI Port";

	case MidiMetaEvent_Unknown:          return "Unknown Meta Event Type";
	default:                             return "BAD META EVENT TYPE";
  }
}

std::string const InstrumentNames[InstrumentCount] = {
	"Acoustic Grand Piano",
	"Bright Acoustic Piano",
	"Electric Grand Piano",
	"Honky-tonk Piano",
	"Electric Piano 1",
	"Electric Piano 2",
	"Harpsichord",
	"Clavi",
	"Celesta",
	"Glockenspiel",
	"Music Box",
	"Vibraphone",
	"Marimba",
	"Xylophone",
	"Tubular Bells",
	"Dulcimer",
	"Drawbar Organ",
	"Percussive Organ",
	"Rock Organ",
	"Church Organ",
	"Reed Organ",
	"Accordion",
	"Harmonica",
	"Tango Accordion",
	"Acoustic Guitar (nylon)",
	"Acoustic Guitar (steel)",
	"Electric Guitar (jazz)",
	"Electric Guitar (clean)",
	"Electric Guitar (muted)",
	"Overdriven Guitar",
	"Distortion Guitar",
	"Guitar harmonics",
	"Acoustic Bass",
	"Electric Bass (finger)",
	"Electric Bass (pick)",
	"Fretless Bass",
	"Slap Bass 1",
	"Slap Bass 2",
	"Synth Bass 1",
	"Synth Bass 2",
	"Violin",
	"Viola",
	"Cello",
	"Contrabass",
	"Tremolo Strings",
	"Pizzicato Strings",
	"Orchestral Harp",
	"Timpani",
	"String Ensemble 1",
	"String Ensemble 2",
	"SynthStrings 1",
	"SynthStrings 2",
	"Choir Aahs",
	"Voice Oohs",
	"Synth Voice",
	"Orchestra Hit",
	"Trumpet",
	"Trombone",
	"Tuba",
	"Muted Trumpet",
	"French Horn",
	"Brass Section",
	"SynthBrass 1",
	"SynthBrass 2",
	"Soprano Sax",
	"Alto Sax",
	"Tenor Sax",
	"Baritone Sax",
	"Oboe",
	"English Horn",
	"Bassoon",
	"Clarinet",
	"Piccolo",
	"Flute",
	"Recorder",
	"Pan Flute",
	"Blown Bottle",
	"Shakuhachi",
	"Whistle",
	"Ocarina",
	"Lead 1 (square)",
	"Lead 2 (sawtooth)",
	"Lead 3 (calliope)",
	"Lead 4 (chiff)",
	"Lead 5 (charang)",
	"Lead 6 (voice)",
	"Lead 7 (fifths)",
	"Lead 8 (bass + lead)",
	"Pad 1 (new age)",
	"Pad 2 (warm)",
	"Pad 3 (polysynth)",
	"Pad 4 (choir)",
	"Pad 5 (bowed)",
	"Pad 6 (metallic)",
	"Pad 7 (halo)",
	"Pad 8 (sweep)",
	"FX 1 (rain)",
	"FX 2 (soundtrack)",
	"FX 3 (crystal)",
	"FX 4 (atmosphere)",
	"FX 5 (brightness)",
	"FX 6 (goblins)",
	"FX 7 (echoes)",
	"FX 8 (sci-fi)",
	"Sitar",
	"Banjo",
	"Shamisen",
	"Koto",
	"Kalimba",
	"Bag pipe",
	"Fiddle",
	"Shanai",
	"Tinkle Bell",
	"Agogo",
	"Steel Drums",
	"Woodblock",
	"Taiko Drum",
	"Melodic Tom",
	"Synth Drum",
	"Reverse Cymbal",
	"Guitar Fret Noise",
	"Breath Noise",
	"Seashore",
	"Bird Tweet",
	"Telephone Ring",
	"Helicopter",
	"Applause",
	"Gunshot",

	//
	// NOTE: These aren't actually General MIDI instruments!
	//
	"Percussion", // for Tracks that use Channel 10 or 16
	"Various"     // for Tracks that use more than one
};
