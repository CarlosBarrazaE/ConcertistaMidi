#version 130
#extension GL_ARB_explicit_attrib_location : enable
layout (location = 0) in vec4 vertices;
out vec2 coordenadas_textura_texto;

uniform mat4 proyeccion;
uniform mat4 modelo;

void main()
{
	gl_Position = proyeccion * modelo * vec4(vertices.xy, 0.0, 1.0);
	coordenadas_textura_texto = vertices.zw;
}
