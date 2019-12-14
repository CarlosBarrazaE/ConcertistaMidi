#ifndef IMAGEN_TGA
#define IMAGEN_TGA

#include <string>

#include "../registro.h++"

namespace Archivo
{
	class Tga
	{
	private:
		unsigned char * m_datos_imagen;
		unsigned int m_ancho_imagen = 0;
		unsigned int m_alto_imagen = 0;
		unsigned int m_bytes_imagen = 0;//Bits por pixel
		bool m_error = false;

	public:
		Tga(std::string direccion);
		~Tga();

		unsigned char * imagen();
		unsigned int ancho();
		unsigned int alto();
		unsigned int bytes();

		bool hay_error();
	};
}

#endif
