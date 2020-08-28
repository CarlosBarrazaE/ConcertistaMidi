#include "sombreador.h++"

unsigned int Sombreador::Ultimo_indice_seleccionado = 0;

Sombreador::Sombreador(const char* codigo_vertice, const char* codigo_fragmento)
{
	int exito;
	unsigned int indice_vertice, indice_fragmento;

	//Se crea el sombreador de vertices
	indice_vertice = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(indice_vertice, 1, &codigo_vertice, NULL);
	glCompileShader(indice_vertice);
	glGetShaderiv(indice_vertice, GL_COMPILE_STATUS, &exito);
	if(!exito)
	{
		Registro::Error("Error al compilar el sombreador de vertices indice: " + std::to_string(indice_vertice));
		comprobar_error_sombreador(indice_vertice);
		indice_vertice = 0;
	}

	//Se crea el sombreador de fragmentos
	indice_fragmento = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(indice_fragmento, 1, &codigo_fragmento, NULL);
	glCompileShader(indice_fragmento);
	glGetShaderiv(indice_fragmento, GL_COMPILE_STATUS, &exito);
	if(!exito)
	{
		Registro::Error("Error al compilar el sombreador de fragmentos indice: " + std::to_string(indice_fragmento));
		comprobar_error_sombreador(indice_fragmento);
		indice_fragmento = 0;
	}

	//Se crea el programa
	m_indice_programa = glCreateProgram();
	glAttachShader(m_indice_programa, indice_vertice);
	glAttachShader(m_indice_programa, indice_fragmento);
	glLinkProgram(m_indice_programa);
	glGetProgramiv(m_indice_programa, GL_LINK_STATUS, &exito);
	if(!exito)
	{
		Registro::Error("Error al compilar el programa indice: " + std::to_string(m_indice_programa));
		comprobar_error_programas(m_indice_programa);
	}
	imprimir_detalle_programa(m_indice_programa);

	glDeleteShader(indice_vertice);
	glDeleteShader(indice_fragmento);
}

Sombreador::~Sombreador()
{
	glUseProgram(0);
	glDeleteProgram(m_indice_programa);
}

void Sombreador::activar()
{
	if(Sombreador::Ultimo_indice_seleccionado != m_indice_programa)
	{
		Sombreador::Ultimo_indice_seleccionado = m_indice_programa;
		glUseProgram(m_indice_programa);
	}
}

unsigned int Sombreador::o_indice()
{
	return m_indice_programa;
}

void Sombreador::uniforme_bool(const std::string &nombre, bool valor)
{
	this->activar();
	glUniform1i(glGetUniformLocation(m_indice_programa, nombre.c_str()), valor);
}

void Sombreador::uniforme_int(const std::string &nombre, int valor)
{
	this->activar();
	glUniform1i(glGetUniformLocation(m_indice_programa, nombre.c_str()), valor);
}

void Sombreador::uniforme_float(const std::string &nombre, float valor)
{
	this->activar();
	glUniform1f(glGetUniformLocation(m_indice_programa, nombre.c_str()), valor);
}

void Sombreador::uniforme_vector2f(const std::string &nombre, float x, float y)
{
	this->activar();
	glUniform2f(glGetUniformLocation(m_indice_programa, nombre.c_str()), x, y);
}

void Sombreador::uniforme_vector3f(const std::string &nombre, float x, float y, float z)
{
	this->activar();
	glUniform3f(glGetUniformLocation(m_indice_programa, nombre.c_str()), x, y, z);
}

void Sombreador::uniforme_vector4f(const std::string &nombre, float x, float y, float z, float w)
{
	this->activar();
	glUniform4f(glGetUniformLocation(m_indice_programa, nombre.c_str()), x, y, z, w);
}

void Sombreador::uniforme_matriz4(const std::string &nombre, glm::mat4 valor)
{
	this->activar();
	glUniformMatrix4fv(glGetUniformLocation(m_indice_programa, nombre.c_str()), 1, GL_FALSE, glm::value_ptr(valor));
}

void Sombreador::comprobar_error_sombreador(unsigned int indice) const
{
	int maximo_largo = 2048;
	char estado[2048];
	glGetShaderInfoLog(indice, maximo_largo, NULL, estado);
	Registro::Depurar("Detalle indice " + std::to_string(indice) + ": " + std::string(estado));
}

void Sombreador::comprobar_error_programas(unsigned int indice) const
{
	int maximo_largo = 2048;
	char estado[2048];
	glGetProgramInfoLog(indice, maximo_largo, NULL, estado);
	Registro::Depurar("Detalle indice " + std::to_string(indice) + ": " + std::string(estado));
}

void Sombreador::imprimir_detalle_programa(unsigned int indice) const
{
	char nombre[64];
	char *nombre_largo = NULL;
	int maximo_largo = 64;
	int tamanno = 0;
	int ubicacion = 0;
	GLenum tipo;

	Registro::Depurar("**** Programa sombreador indice: " + std::to_string(indice) + " ****");
	int parametro = -1;
	glGetProgramiv(indice, GL_LINK_STATUS, &parametro);
	Registro::Depurar("GL_LINK_STATUS: " + std::to_string(parametro));

	glGetProgramiv(indice, GL_ATTACHED_SHADERS, &parametro);
	Registro::Depurar("GL_ATTACHED_SHADERS: " + std::to_string(parametro));

	glGetProgramiv(indice, GL_ACTIVE_ATTRIBUTES, &parametro);
	Registro::Depurar("GL_ACTIVE_ATTRIBUTES: " + std::to_string(parametro));

	for(int x=0; x<parametro; x++)
	{
		glGetActiveAttrib(indice, x, maximo_largo, NULL, &tamanno, &tipo, nombre);
		if(tamanno > 1)
		{
			for(int y=0; y<tamanno; y++)
			{
				sprintf(nombre_largo, "%s[%i]", nombre, y);
				ubicacion = glGetAttribLocation(indice, nombre_largo);
				Registro::Depurar("\tTipo: " + GL_tipo_a_texto(tipo) + " Nombre: " + std::string(nombre_largo) + " Ubicacion: " + std::to_string(ubicacion));
			}
		}
		else
		{
			ubicacion = glGetAttribLocation(indice, nombre);
			Registro::Depurar("\tTipo: " + GL_tipo_a_texto(tipo) + " Nombre: " + std::string(nombre) + " Ubicacion: " + std::to_string(ubicacion));
		}
	}

	glGetProgramiv(indice, GL_ACTIVE_UNIFORMS, &parametro);
	Registro::Depurar("GL_ACTIVE_UNIFORMS: " + std::to_string(parametro));

	for(int x=0; x<parametro; x++)
	{
		glGetActiveUniform(indice, x, maximo_largo, NULL, &tamanno, &tipo, nombre);
		if(tamanno > 1)
		{
			for(int y=0; y<tamanno; y++)
			{
				sprintf(nombre_largo, "%s[%i]", nombre, y);
				ubicacion = glGetUniformLocation(indice, nombre_largo);
				Registro::Depurar("\tTipo: " + GL_tipo_a_texto(tipo) + " Nombre: " + std::string(nombre_largo) + " Ubicacion: " + std::to_string(ubicacion));
			}
		}
		else
		{
			ubicacion = glGetUniformLocation(indice, nombre);
			Registro::Depurar("\tTipo: " + GL_tipo_a_texto(tipo) + " Nombre: " + std::string(nombre) + " Ubicacion: " + std::to_string(ubicacion));
		}
	}
}

std::string Sombreador::GL_tipo_a_texto(GLenum tipo) const
{
	switch(tipo)
	{
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "textura2D";
		case GL_SAMPLER_3D: return "textura3D";
		case GL_SAMPLER_CUBE: return "texturaCubo";
		case GL_SAMPLER_2D_SHADOW: return "texturaCuboSombra";
		default: break;
	}
	return "Otro";
}
