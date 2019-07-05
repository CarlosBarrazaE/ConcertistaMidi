#version 460
out vec4 fragmento_color;

in vec2 textura_posicion;

uniform sampler2D textura;
uniform vec4 color;
uniform bool textura_activada;
uniform bool textura_estirable;
uniform float borde;
float coordenada_nueva_y = 0;

float map(float valor, float o_minimo, float o_maximo, float n_minimo, float n_maximo)
{
	return (valor - o_minimo) / (o_maximo - o_minimo) * (n_maximo - n_minimo) + n_minimo;
}

void main()
{
	if(textura_activada)
	{
		if(textura_estirable)
		{
			if(textura_posicion.y < borde)
				coordenada_nueva_y = map(textura_posicion.y, 0, borde, 0, 0.5);
			else if(textura_posicion.y > 1-borde)
				coordenada_nueva_y = map(textura_posicion.y, 1-borde, 1, 0.5, 1);
			else
				coordenada_nueva_y = 0.5;

			fragmento_color = texture(textura, vec2(textura_posicion.x, coordenada_nueva_y)) * color;
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
