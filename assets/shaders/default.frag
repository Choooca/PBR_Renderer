#version 330 core
out vec4 FragColor;

in vec2 TexCoord0;

uniform vec3 object_color;
uniform vec3 light_color;

uniform sampler2D texture_sample;

void main()
{
	FragColor = vec4(object_color * light_color, 1.0f) * texture(texture_sample, TexCoord0);
}
