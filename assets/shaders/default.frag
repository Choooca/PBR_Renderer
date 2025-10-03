#version 330 core
out vec4 FragColor;

in vec2 TexCoord0;
uniform vec4 base_color;
uniform sampler2D texture1;

void main()
{
	vec2 tex_fix = vec2(TexCoord0.x, 1.0f - TexCoord0.y);
	FragColor = base_color * texture(texture1, tex_fix);	
}