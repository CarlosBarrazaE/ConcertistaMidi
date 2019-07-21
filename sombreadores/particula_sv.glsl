#version 130
#extension GL_ARB_explicit_attrib_location : enable
layout (location = 0) in vec2 posicion_vertice;
layout (location = 1) in vec2 coordenadas_textura;

out vec2 textura_posicion;

uniform mat4 proyeccion;
uniform vec2 posicion;
uniform float escala;

void main()
{
	gl_Position = proyeccion * vec4((posicion_vertice * escala) + posicion, 0.0, 1.0);
	textura_posicion = coordenadas_textura;
}
