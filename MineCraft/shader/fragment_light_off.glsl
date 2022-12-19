#version 330 core

out vec4 FragColor;  

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 objectColor;

void main()
{
	float ambientLight = 0.3;
	vec3 ambient = ambientLight * lightColor;

	FragColor = vec4(ambient * objectColor, 1.0);
}
