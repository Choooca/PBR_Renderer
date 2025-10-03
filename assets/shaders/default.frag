#version 330 core
out vec4 FragColor;

in vec2 TexCoord0;

void main()
{
	FragColor = vec4(TexCoord0.x, TexCoord0.y, 1.0f, 1.0f);	
}