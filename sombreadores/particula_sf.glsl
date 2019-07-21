#version 130
out vec4 fragmento_color;

in vec2 textura_posicion;

uniform sampler2D textura;
uniform vec4 color;

void main()
{
	fragmento_color = texture(textura, textura_posicion) * color;
}
