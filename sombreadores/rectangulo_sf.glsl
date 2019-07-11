#version 460
out vec4 fragmento_color;

in vec2 textura_posicion;

uniform sampler2D textura;
uniform vec4 color;
uniform bool textura_activada;
uniform bool textura_estirable_horizontal;
uniform bool textura_estirable_vertical;
uniform vec2 borde;

float coordenada_nueva_x = 0;
float coordenada_nueva_y = 0;

float map(float valor, float o_minimo, float o_maximo, float n_minimo, float n_maximo)
{
	return (valor - o_minimo) / (o_maximo - o_minimo) * (n_maximo - n_minimo) + n_minimo;
}

void main()
{
	if(textura_activada)
	{
		if(textura_estirable_horizontal || textura_estirable_vertical)
		{
			if(textura_estirable_horizontal)
			{
				if(textura_posicion.x < borde.x)
					coordenada_nueva_x = map(textura_posicion.x, 0, borde.x, 0, 0.5);
				else if(textura_posicion.x > 1-borde.x)
					coordenada_nueva_x = map(textura_posicion.x, 1-borde.x, 1, 0.5, 1);
				else
					coordenada_nueva_x = 0.5;
			}
			else
			{
				coordenada_nueva_x = textura_posicion.x;
			}

			if(textura_estirable_vertical)
			{
				if(textura_posicion.y < borde.y)
					coordenada_nueva_y = map(textura_posicion.y, 0, borde.y, 0, 0.5);
				else if(textura_posicion.y > 1-borde.y)
					coordenada_nueva_y = map(textura_posicion.y, 1-borde.y, 1, 0.5, 1);
				else
					coordenada_nueva_y = 0.5;
			}
			else
			{
				coordenada_nueva_y = textura_posicion.y;
			}

			fragmento_color = texture(textura, vec2(coordenada_nueva_x, coordenada_nueva_y)) * color;
		}
		else
		{
			fragmento_color = texture(textura, textura_posicion) * color;
		}
	}
	else
	{
		fragmento_color = color;
	}
}
