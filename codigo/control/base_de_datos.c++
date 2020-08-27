#include "base_de_datos.h++"

Base_de_Datos::Base_de_Datos()
{
}

Base_de_Datos::~Base_de_Datos()
{
	//Cerrar solo si esta abierta
	sqlite3_close(m_base_de_datos);
}

bool Base_de_Datos::consulta(std::string consulta_entrada)
{
	char *error = 0;
	int respuesta = sqlite3_exec(m_base_de_datos, consulta_entrada.c_str(), NULL, 0, &error);
	if(!respuesta == SQLITE_OK)
	{
		Registro::Error(std::string(error));
		sqlite3_free(error);
        return false;
	}
	return true;
}

int Base_de_Datos::consulta_int(std::string consulta)
{
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

bool Base_de_Datos::abrir(std::string direccion)
{
	int respuesta = sqlite3_open(direccion.c_str(), &m_base_de_datos);
	return true;//Fala comprobar si se abre correctamente la base de datos
}

void Base_de_Datos::crear()
{
	//Crea todas las tablas de la base de datos
	this->consulta("CREATE TABLE configuracion (atributo VARCHAR(30), valor TEXT)");

	this->escribir_configuracion("version_base_de_datos", VERSION_BASE_DE_DATOS);
}

void Base_de_Datos::actualizar()
{
	//Verificar version de la base de datos
	std::string version_texto = this->leer_configuracion("version_base_de_datos");
	std::replace(version_texto.begin(), version_texto.end(), '.', ',');
	double version_bd = std::strtod(version_texto.c_str(), NULL);

	Registro::Nota("Version de la base de datos: " + version_texto);
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
