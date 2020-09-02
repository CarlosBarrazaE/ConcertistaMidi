#include "etiqueta.h++"

Color Etiqueta::Ultimo_color;

Etiqueta::Etiqueta(Administrador_Recursos *recursos) : Elemento(0, 0, 0, 0)
{
	m_sombreador = recursos->sombreador(S_Texto);
}

Etiqueta::Etiqueta(int x, int y, bool centrado, std::string texto, ModeloLetra tipografia, Administrador_Recursos *recursos) : Elemento(x, y, 0, 0, centrado)
{
	m_texto_actual = texto;
	m_texto = texto.c_str();
	m_tipografia = recursos->tipografia(tipografia);
	m_sombreador = recursos->sombreador(S_Texto);
	this->actualizar_texto();
}

Etiqueta::Etiqueta(int x, int y, bool centrado, std::string texto, Tipografia *tipografia, Administrador_Recursos *recursos) : Elemento(x, y, 0, 0, centrado)
{
	m_texto_actual = texto;
	m_texto = texto.c_str();
	m_tipografia = tipografia;
	m_sombreador = recursos->sombreador(S_Texto);
	this->actualizar_texto();
}

Etiqueta::Etiqueta(int x, int y, int ancho, int alto, bool centrado, std::string texto, ModeloLetra tipografia, Administrador_Recursos *recursos) : Elemento(x, y, ancho, alto, centrado)
{
	m_texto_actual = texto;
	m_texto = texto.c_str();
	m_tipografia = recursos->tipografia(tipografia);
	m_sombreador = recursos->sombreador(S_Texto);
	this->actualizar_texto();
}

Etiqueta::~Etiqueta()
{
	this->limpiar();
}

void Etiqueta::limpiar()
{
	if(m_indice_figura > 0)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &m_indice_figura);
	}
	if(m_indice_objeto > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_indice_objeto);
	}
}

void Etiqueta::actualizar_texto()
{
	if(m_tipografia != NULL && m_texto.length() > 0)
	{
		this->limpiar();
		m_ancho_texto = m_tipografia->crear_texto(m_texto, &m_indice_figura, &m_indice_objeto);
		m_alto_texto = m_tipografia->alto_texto();
	}
	else
	{
		m_ancho_texto = 0;
		m_alto_texto = 0;
	}
}

void Etiqueta::actualizar(unsigned int /*diferencia_tiempo*/)
{
}

void Etiqueta::dibujar()
{
	if(m_texto.length() == 0)
		return;

	if(m_tipografia == NULL)
		return;

	int nueva_x = 0;
	int nueva_y = 0;
	if(m_centrado)
	{
		if(this->alto() == 0)
		{
			nueva_x = this->x()+this->dx()+this->ancho()/2.0 - m_ancho_texto / 2.0;
			nueva_y = this->y()+this->dy()+m_tipografia->alto_texto();
		}
		else
		{
			nueva_x = this->x()+this->dx()+this->ancho()/2.0 - m_ancho_texto / 2.0;
			nueva_y = this->y()+this->dy()+m_tipografia->alto_texto()+this->alto()/2.0-m_tipografia->alto_texto()/2.0;
		}
	}
	else
	{
		nueva_x = this->x()+this->dx();
		nueva_y = this->y()+this->dy()+m_tipografia->alto_texto();
	}


	//TODO ¿Esto deberia estar a cargo de la tipografia?
	glm::mat4 modelo = glm::mat4(1.0f);
	modelo = glm::translate(modelo, glm::vec3(nueva_x, nueva_y, 0.0f));
	//modelo = glm::scale(modelo, glm::vec3(ancho, alto, 1.0f));

	m_sombreador->activar();
	m_sombreador->uniforme_matriz4("modelo", modelo);
	if(Etiqueta::Ultimo_color != m_color)
	{
		m_sombreador->uniforme_vector3f("color_texto", m_color.rojo(), m_color.verde(), m_color.azul());
		Etiqueta::Ultimo_color = m_color;
	}

	if(Figura::Ultimo_indice_seleccionado != m_indice_objeto)
	{
		glBindVertexArray(m_indice_objeto);
		Figura::Ultimo_indice_seleccionado = m_indice_objeto;
	}
	m_tipografia->activar();
	glDrawArrays(GL_TRIANGLES, 0, m_texto.length()*6);
}

void Etiqueta::evento_raton(Raton */*raton*/)
{
}

void Etiqueta::evento_pantalla(int /*ancho*/, int /*alto*/)
{
}

void Etiqueta::texto(std::string texto)
{
	//No se vuelve a crear el mismo texto dos veces
	if(m_texto_actual != texto)
		m_texto_actual = texto;
	else
		return;
	m_texto = texto.c_str();
	this->actualizar_texto();
}

void Etiqueta::color(Color color)
{
	m_color = color;
}

void Etiqueta::tipografia(Tipografia *tipografia)
{
	m_tipografia = tipografia;
	m_alto_texto = m_tipografia->alto_texto();
	this->actualizar_texto();
}

void Etiqueta::centrado(bool centrado)
{
	m_centrado = centrado;
}

int Etiqueta::largo_texto()
{
	return m_ancho_texto;
}

int Etiqueta::alto_texto()
{
	return m_alto_texto;
}

std::string Etiqueta::texto()
{
	return m_texto_actual;
}
