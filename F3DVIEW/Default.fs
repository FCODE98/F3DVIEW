#version 330 core

in vec3 pColor;
out vec4 FragColor;

in vec2 pTex;

uniform sampler2D tex0;

void main()
{
	FragColor = texture(tex0 , pTex);
}