#version 150
// Fragment Shader

in vec3 Colour;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float fadeTime;
uniform float time;
uniform bool reflection;

void main()
{
	vec4 colKitten;
	vec4 colPuppy; 

	float texX;

	vec2 reflectCoord;

	reflectCoord = Texcoord;

	if(reflection)
	{
		reflectCoord.x += sin(Texcoord.y * 60.0f + time * 2.0f)/ 30.0f;
	}



    /*if(Texcoord.y <= 0.5)
	{*/
		colKitten = texture(texKitten, reflectCoord);
		colPuppy = texture(texPuppy, reflectCoord);
	/*}
	else
	{
		vec2 superReflectCoord = vec2(reflectCoord.x + sin(reflectCoord.y * 60.0f + time * 2.0f)/ 30.0f, 1.0f - reflectCoord.y);

		colKitten = texture(texKitten, superReflectCoord);
		colPuppy = texture(texPuppy, superReflectCoord);
	}*/

	

	float mixAmount = (sin(fadeTime * (time/1000)) + 1.0f / 2.0f);

	if (mixAmount > 1.0f) mixAmount = 1.0f;
	else if (mixAmount < 0.0f) mixAmount = 0.0f;

	outColour = mix(colKitten, colPuppy, mixAmount) * vec4(Colour, 1.0f);
}