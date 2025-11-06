#version 330 core
out vec4 FragColor;

uniform vec3 object_color;
uniform vec3 light_color;
uniform float ambient_strength;
uniform vec3 light_pos;

in vec3 Normal;
in vec3 FragPos;

//https://www.amazon.com/Mathematics-Programming-Computer-Graphics-Second/dp/1584502770
// http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/

void main()
{
  vec3 normal = normalize(Normal);
  vec3 light_dir = normalize(light_pos - FragPos);
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = ambient_strength * light_color;

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = dot_normal_light * light_color;

  float specular_strength = 0.5f;
  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
  vec3 specular = specular_strength * specular_factor * light_color;

  vec3 result = ( diffuse + ambient + specular) * object_color;

	FragColor = vec4(result, 1.0f);
}
