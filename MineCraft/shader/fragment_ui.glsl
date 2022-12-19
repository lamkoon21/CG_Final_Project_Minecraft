#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D outTexture;

void main()
{
	vec4 texColor = texture(outTexture, TexCoord);
	if(texColor.a < 0.1)
		discard;
	FragColor = texColor;
}
