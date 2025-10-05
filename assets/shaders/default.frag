#version 330 core
out vec4 FragColor;

in vec2 TexCoord0;

uniform sampler2D texture_sample;

void main()
{
	FragColor = texture(texture_sample, TexCoord0);
}