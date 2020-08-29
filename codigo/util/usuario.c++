#ifdef __linux__
#include <unistd.h>//getuid
#include <pwd.h>//getpwuid
#endif
#include "usuario.h++"

namespace Usuario
{
	std::string carpeta_personal()
	{
	#ifdef __linux__
		const char *carpeta = 0;
		carpeta = getenv("HOME");
		if(carpeta == 0)
		{
			struct passwd *usuario = getpwuid(getuid());
			if(usuario)
				carpeta = usuario->pw_dir;
		}
		return std::string(carpeta) + "/";
	#elif _WIN32
		//Falta funcion para windows
		return std::string("");
	#endif
	}
}
