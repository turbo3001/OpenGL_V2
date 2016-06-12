#version 150

// Vertex Shader

in vec3 position;
in vec3 colour;
in vec2 texcoord;

out vec3 Colour;
out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 overrideColour;

void main()
{
	Texcoord = texcoord;
	Colour = overrideColour * colour;
    gl_Position = projection * view * model * vec4(position, 1.0);
}