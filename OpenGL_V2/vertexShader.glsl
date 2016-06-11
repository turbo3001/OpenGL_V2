#version 150

in vec3 position;
in vec3 colour;
in vec2 texcoord;

out vec3 Colour;
out vec2 Texcoord;

uniform mat4 transform;

void main()
{
	Texcoord = texcoord;
	Colour = colour;
    gl_Position = transform * vec4(position, 1.0);
}