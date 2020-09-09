#include "base_de_datos.h++"

Base_de_Datos::Base_de_Datos()
{
	m_base_de_datos_abierta = false;
}

Base_de_Datos::~Base_de_Datos()
{
	if(m_base_de_datos_abierta)
		sqlite3_close(m_base_de_datos);
}

bool Base_de_Datos::consulta(std::string consulta_entrada)
{
	if(!m_base_de_datos_abierta)
	{
		Registro::Error("La base de datos no esta abierta");
		return false;
	}
	char *error = 0;
	int respuesta = sqlite3_exec(m_base_de_datos, consulta_entrada.c_str(), NULL, 0, &error);
	if(respuesta != SQLITE_OK)
	{
		Registro::Error(std::string(error));
		sqlite3_free(error);
        return false;
	}
	return true;
}

int Base_de_Datos::consulta_int(std::string consulta)
{
	if(!m_base_de_datos_abierta)
	{
		Registro::Error("La base de datos no esta abierta");
		return 0;
	}
	sqlite3_stmt * respuesta_consulta;
	int respuesta = sqlite3_prepare(m_base_de_datos, consulta.c_str(), -1, &respuesta_consulta, NULL);
	int resultado = 0;
	if(respuesta == SQLITE_OK)
	{
		sqlite3_step(respuesta_consulta);
		resultado = sqlite3_column_int(respuesta_consulta, 0);
	}
	sqlite3_finalize(respuesta_consulta);
	return resultado;
}

std::string Base_de_Datos::consulta_texto(std::string consulta)
{
	if(!m_base_de_datos_abierta)
	{
		Registro::Error("La base de datos no esta abierta");
		return "";
	}
	sqlite3_stmt * respuesta_consulta;
	int respuesta = sqlite3_prepare(m_base_de_datos, consulta.c_str(), -1, &respuesta_consulta, NULL);
	if(respuesta == SQLITE_OK)
	{
		sqlite3_step(respuesta_consulta);
		if(sqlite3_column_text(respuesta_consulta, 0) != 0)
		{
			std::string texto = std::string((char*)sqlite3_column_text(respuesta_consulta, 0));
			sqlite3_finalize(respuesta_consulta);
			return texto;
		}
	}
	sqlite3_finalize(respuesta_consulta);
	return "";
}

std::vector<std::vector<std::string>> Base_de_Datos::consulta_tabla(std::string consulta, int columnas)
{
	sqlite3_stmt * respuesta_consulta;
	int respuesta = sqlite3_prepare(m_base_de_datos, consulta.c_str(), -1, &respuesta_consulta, NULL);
	std::vector<std::vector<std::string>> tabla;
	if(respuesta == SQLITE_OK)
	{
		sqlite3_step(respuesta_consulta);
		int x = 0;
		while(sqlite3_column_text(respuesta_consulta, 0))
		{
			tabla.push_back(std::vector<std::string>());
			for(int c=0; c<columnas; c++)
			{
				tabla[x].push_back(std::string((char*)sqlite3_column_text(respuesta_consulta, c)));
			}
			sqlite3_step(respuesta_consulta);
			x++;
		}
	}
	sqlite3_finalize(respuesta_consulta);
	return tabla;
}

bool Base_de_Datos::abrir(std::string direccion)
{
	int respuesta = sqlite3_open(direccion.c_str(), &m_base_de_datos);
	if(respuesta != SQLITE_OK)
	{
		Registro::Error("No se puede abrir o crear la base de datos.");
		m_base_de_datos_abierta = false;
		return true;
	}
	m_base_de_datos_abierta = true;
	return false;
}

void Base_de_Datos::crear()
{
	//Crea todas las tablas de la base de datos
	this->consulta("CREATE TABLE configuracion (atributo VARCHAR(30), valor TEXT)");
	this->consulta("CREATE TABLE carpetas (nombre VARCHAR(30) NOT NULL PRIMARY KEY, ruta TEXT)");

	this->escribir_configuracion("version_base_de_datos", VERSION_BASE_DE_DATOS);
	this->ruta_carpeta("Canciones", "../musica/");
}

void Base_de_Datos::actualizar()
{
	//Verificar version de la base de datos
	std::string version_texto = this->leer_configuracion("version_base_de_datos");
	Registro::Nota("Version de la base de datos: " + version_texto);
	if(version_texto != "")
	{
		/*
		double version_bd = std::stod(version_texto, NULL);
		*/
	}
}

//Tabla configuracion
bool Base_de_Datos::escribir_configuracion(std::string atributo, std::string valor)
{
	if(atributo.size() > 30)
	{
		Registro::Error("Nombre del atributo '"+atributo+"' es demaciado largo, maximo 30");
		return false;
	}
	if(valor != "")
	{
		Registro::Depurar("Escribiendo el registro: " + atributo + "->"+valor);
		//No se aceptan atributos vacios
		if(this->leer_configuracion(atributo).size() == 0)
			this->consulta("INSERT INTO configuracion ('atributo', 'valor') VALUES ('"+atributo+"', '"+valor+"')");
		else
			this->consulta("UPDATE configuracion SET valor = '"+valor+"' WHERE atributo = '"+atributo+"'");
		return true;
	}
	else
	{
		Registro::Error("Atributo: " + atributo + " con valor vacio.");
		return false;
	}
}

std::string Base_de_Datos::leer_configuracion(std::string atributo)
{
	if(atributo.size() > 30)
	{
		Registro::Error("Nombre del atributo '"+atributo+"' es demaciado largo, maximo 30");
		return "";
	}
	return this->consulta_texto("SELECT valor FROM configuracion WHERE atributo = '"+atributo+"' LIMIT 1");
}

bool Base_de_Datos::ruta_carpeta(std::string nombre, std::string ruta)
{
	return this->consulta("INSERT INTO carpetas ('nombre', 'ruta') VALUES ('"+nombre+"', '"+ruta+"')");
}

std::vector<std::vector<std::string>> Base_de_Datos::ruta_carpetas()
{
	return this->consulta_tabla("SELECT * FROM carpetas", 2);
}

bool Base_de_Datos::eliminar_ruta_carpeta(std::string nombre)
{
	return this->consulta("DELETE FROM carpetas WHERE nombre = '"+nombre+"'");
}
