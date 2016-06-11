#version 150

in vec3 Colour;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float deltaTime;
uniform float time;

void main()
{
	vec4 colKitten;
	vec4 colPuppy; 
    if(Texcoord.y <= 0.5)
	{
		colKitten = texture(texKitten, Texcoord);
		colPuppy = texture(texPuppy, Texcoord);
	}
	else
	{
		vec2 reflectCoord = vec2(Texcoord.x + sin(Texcoord.y * 60.0f + time * 2.0f)/ 30.0f, 1.0f - Texcoord.y);

		colKitten = texture(texKitten, reflectCoord);
		colPuppy = texture(texPuppy, reflectCoord);
	}

	

	float mixAmount = (sin(deltaTime * (time/1000)) + 1.0f / 2.0f);

	if (mixAmount > 1.0f) mixAmount = 1.0f;
	else if (mixAmount < 0.0f) mixAmount = 0.0f;

	outColour = mix(colKitten, colPuppy, mixAmount) * vec4(Colour, 1.0f);
}