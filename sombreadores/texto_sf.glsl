#version 130
in vec2 coordenadas_textura_texto;
out vec4 color_salida;

uniform sampler2D textura_texto;
uniform vec3 color_texto;

void main()
{
	vec4 muestra = vec4(1.0, 1.0, 1.0, texture(textura_texto, coordenadas_textura_texto).r);
	color_salida = vec4(color_texto.x, color_texto.y, color_texto.z, 1.0) * muestra;
}
