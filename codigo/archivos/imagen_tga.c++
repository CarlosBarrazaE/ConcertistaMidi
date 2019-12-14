#include "imagen_tga.h++"

namespace Archivo
{
	Tga::Tga(std::string direccion)
	{
		//GLubyte cabeceraSinCompresionTGA[12] = {0,0,2,0,0,0,0,0,0,0,0,0};
		unsigned char cabeceraTGA[12];
		unsigned char cabecera[6];
		unsigned int tamanno_imagen = 0;
		unsigned int bpp = 0;
		unsigned int temporal = 0;

		FILE *archivo = fopen(direccion.c_str(), "rb");

		if(archivo != NULL)
		{
			if(fread(cabeceraTGA, 1, sizeof(cabeceraTGA), archivo) == sizeof(cabeceraTGA))
			{
				if(cabeceraTGA[2] == 2)
				{
					if(fread(cabecera, 1, sizeof(cabecera), archivo) == sizeof(cabecera))
					{
						//La cabecera contiene: ancho, alto y los bpp
						//El ancho se guarda en cabecera[0] y cabecera[1] para leerlo hay que multiplicar cabecera[1]*256
						m_ancho_imagen = 256 * cabecera[1] + cabecera[0];
						m_alto_imagen = 256 * cabecera[3] + cabecera[2];

						if(m_ancho_imagen > 0 && m_alto_imagen > 0)
						{
							m_bytes_imagen = cabecera[4];
							bpp = (m_bytes_imagen/8);//bytes por pixel
							tamanno_imagen  = m_alto_imagen * m_ancho_imagen * bpp;

							m_datos_imagen = new unsigned char[tamanno_imagen];

							if(fread(m_datos_imagen, 1, tamanno_imagen, archivo) == tamanno_imagen)
							{
								for(unsigned int x=0; x<(int)tamanno_imagen; x+=bpp)
								{
									temporal = m_datos_imagen[x];
									m_datos_imagen[x] = m_datos_imagen[x+2];
									m_datos_imagen[x+2] = temporal;
								}
							}
						}
					}
				}
			}
			fclose(archivo);
		}
		else
		{
			Registro::Error("Error al leer la textura: " + direccion);
			m_error = true;
			m_datos_imagen = NULL;
		}
	}

	Tga::~Tga()
	{
		delete[] m_datos_imagen;
	}

	unsigned char * Tga::imagen()
	{
		return this->m_datos_imagen;
	}

	unsigned int Tga::ancho()
	{
		return this->m_ancho_imagen;
	}

	unsigned int Tga::alto()
	{
		return this->m_alto_imagen;
	}

	unsigned int Tga::bytes()
	{
		return this->m_bytes_imagen;
	}

	bool Tga::hay_error()
	{
		return this->m_error;
	}
}
