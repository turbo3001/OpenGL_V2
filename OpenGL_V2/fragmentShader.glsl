#version 150

in vec3 Colour;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float mixAmount;

void main()
{
	vec4 colKitten = texture(texKitten, Texcoord);
	vec4 colPuppy = texture(texPuppy, Texcoord);
    outColour = mix(colKitten, colPuppy, mixAmount) * vec4(Colour, 1.0f);
}