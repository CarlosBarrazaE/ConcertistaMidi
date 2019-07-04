#version 460
out vec4 fragmento_color;

in vec2 textura_posicion;

uniform sampler2D textura;
uniform vec4 color;
uniform bool textura_activada;

void main()
{
	if(textura_activada)
		fragmento_color = texture(textura, textura_posicion) * color;
	else
		fragmento_color = color;
}
