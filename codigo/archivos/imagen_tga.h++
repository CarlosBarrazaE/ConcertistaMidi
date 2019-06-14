#ifndef IMAGEN_TGA
#define IMAGEN_TGA

#include <string>

#include "../registro.h++"

namespace Archivo
{
	class Tga
	{
	private:
		unsigned char * datos_imagen;
		unsigned int ancho_imagen = 0;
		unsigned int alto_imagen = 0;
		unsigned int bytes_imagen = 0;//Bits por pixel
		bool error = false;

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
