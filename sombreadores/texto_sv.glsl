#version 460
layout (location = 0) in vec4 vertices;
out vec2 coordenadas_textura_texto;

uniform mat4 proyeccion;

void main()
{
	gl_Position = proyeccion * vec4(vertices.xy, 0.0, 1.0);
	coordenadas_textura_texto = vertices.zw;
}
