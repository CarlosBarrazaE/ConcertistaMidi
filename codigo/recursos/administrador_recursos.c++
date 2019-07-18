#include "administrador_recursos.h++"

Administrador_Recursos::Administrador_Recursos()
{
	this->ancho = 800;
	this->alto = 600;
	matriz_proyeccion = glm::ortho(0.0f, (float)this->ancho, (float)this->alto, 0.0f, -1.0f, 1.0f);

	archivo_texturas[T_FondoTitulo] = "../texturas/fondo_titulo.tga";
	archivo_texturas[T_Titulo] = "../texturas/titulo.tga";
	archivo_texturas[T_Boton] = "../texturas/boton.tga";
	archivo_texturas[T_TeclaBlanca] = "../texturas/tecla_blanca.tga";
	archivo_texturas[T_TeclaNegra] = "../texturas/tecla_negra.tga";
	archivo_texturas[T_TeclaBlancaPresionada] = "../texturas/tecla_blanca_presionada.tga";
	archivo_texturas[T_TeclaBlancaPresionadaDoble] = "../texturas/tecla_blanca_presionada_doble.tga";
	archivo_texturas[T_TeclaNegraPresionada] = "../texturas/tecla_negra_presionada.tga";
	archivo_texturas[T_BordeOrganoRojo] = "../texturas/borde_organo_rojo.tga";
	archivo_texturas[T_BordeOrganoNegro] = "../texturas/borde_organo_negro.tga";
	archivo_texturas[T_Nota] = "../texturas/nota.tga";
	archivo_texturas[T_Sombra] = "../texturas/sombra.tga";
	archivo_texturas[T_FrenteBarraProgreso] = "../texturas/frente_barra_progreso.tga";
	archivo_texturas[T_ParticulaNota] = "../texturas/particula_nota.tga";
	archivo_texturas[T_Barra] = "../texturas/barra.tga";
	archivo_texturas[T_ConfiguracionPista] = "../texturas/configuracion_pista.tga";
	archivo_texturas[T_SonidoActivado] = "../texturas/sonido_activado.tga";
	archivo_texturas[T_SonidoDesactivado] = "../texturas/sonido_desactivado.tga";
	archivo_texturas[T_Reproducir] = "../texturas/reproducir.tga";
	archivo_texturas[T_Pausar] = "../texturas/pausar.tga";

	archivo_sombreador_vertice[S_Rectangulo] = "../sombreadores/rectangulo_sv.glsl";
	archivo_sombreador_fragmento[S_Rectangulo] = "../sombreadores/rectangulo_sf.glsl";

	archivo_sombreador_vertice[S_Texto] = "../sombreadores/texto_sv.glsl";
	archivo_sombreador_fragmento[S_Texto] = "../sombreadores/texto_sf.glsl";

	archivo_sombreador_vertice[S_Particula] = "../sombreadores/particula_sv.glsl";
	archivo_sombreador_fragmento[S_Particula] = "../sombreadores/particula_sf.glsl";

	lista_figuras[F_Rectangulo] = new Rectangulo(this->obtener_sombreador(S_Rectangulo));

	Sombreador *sombreador_letras = this->obtener_sombreador(S_Texto);
	sombreador_letras->e_int("textura_texto", 0);
	sombreador_letras->e_vector3f("color_texto", 0.0, 0.0, 0.0);

	formato_letras[LetraTitulo] = new Texto(Normal, 20, sombreador_letras);
	formato_letras[LetraGrande] = new Texto(Normal, 16, sombreador_letras);
	formato_letras[LetraMediana] = new Texto(Normal, 14, sombreador_letras);
	formato_letras[LetraChica] = new Texto(Normal, 12, sombreador_letras);
	formato_letras[LetraMuyChica] = new Texto(Normal, 8, sombreador_letras);
}

Administrador_Recursos::~Administrador_Recursos()
{
	for(std::map<Textura, Textura2D*>::iterator i = lista_texturas.begin(); i != lista_texturas.end(); i++)
		delete i->second;
	lista_texturas.clear();

	for(std::map<SombreadorVF, Sombreador*>::iterator i = lista_sombreadores.begin(); i != lista_sombreadores.end(); i++)
		delete i->second;
	lista_sombreadores.clear();

	for(std::map<FiguraGeometrica, Rectangulo*>::iterator i = lista_figuras.begin(); i != lista_figuras.end(); i++)
		delete i->second;
	lista_figuras.clear();
}

Textura2D *Administrador_Recursos::obtener_textura(Textura valor)
{
	Textura2D *temporal = lista_texturas[valor];
	if(!temporal)
	{
		//Generar la textura
		Archivo::Tga textura_nueva(archivo_texturas[valor]);

		temporal = new Textura2D();
		temporal->generar(textura_nueva.ancho(), textura_nueva.alto(), textura_nueva.bytes(), GL_BGR, textura_nueva.imagen());

		lista_texturas[valor] = temporal;

		Registro::depurar("Se cargo la textura del archivo: " + std::string(archivo_texturas[valor]));
	}

	return temporal;
}

Sombreador *Administrador_Recursos::obtener_sombreador(SombreadorVF valor)
{
	Sombreador *temporal = lista_sombreadores[valor];
	if(!temporal)
	{
		std::string texto_vertice = Archivo::leer_archivo(archivo_sombreador_vertice[valor]);
		std::string texto_fragmento = Archivo::leer_archivo(archivo_sombreador_fragmento[valor]);

		const char* codigo_vertice = texto_vertice.c_str();
		const char* codigo_fragmento = texto_fragmento.c_str();

		temporal = new Sombreador(codigo_vertice, codigo_fragmento);
		temporal->e_matriz4("proyeccion", this->matriz_proyeccion);

		lista_sombreadores[valor] = temporal;

		Registro::depurar("Se cargo el sombreador de vertices del archivo: " + std::string(archivo_sombreador_vertice[valor]));
		Registro::depurar("Se cargo el sombreador de fragmentos del archivo: " + std::string(archivo_sombreador_fragmento[valor]));
	}

	return temporal;
}

Rectangulo *Administrador_Recursos::obtener_figura(FiguraGeometrica valor)
{
	return lista_figuras[F_Rectangulo];
}

Texto *Administrador_Recursos::obtener_tipografia(ModeloLetra tipo)
{
	return formato_letras[tipo];
}

void Administrador_Recursos::actualizar_pantalla(int nuevo_ancho, int nuevo_alto)
{
	this->ancho = nuevo_ancho;
	this->alto = nuevo_alto;

	matriz_proyeccion = glm::ortho(0.0f, (float)this->ancho, (float)this->alto, 0.0f, -1.0f, 1.0f);

	for(std::map<SombreadorVF, Sombreador*>::iterator e=lista_sombreadores.begin(); e != lista_sombreadores.end(); e++)
	{
		e->second->e_matriz4("proyeccion", this->matriz_proyeccion);
	}
}
