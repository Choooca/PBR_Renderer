#version 330 core
out vec4 FragColor;

struct Material{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;

uniform Material material;

uniform vec3 object_color;
uniform vec3 light_color;

in vec3 Normal;
in vec3 FragPos;

//https://www.amazon.com/Mathematics-Programming-Computer-Graphics-Second/dp/1584502770
// http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/

void main()
{
  vec3 normal = normalize(Normal);
  vec3 light_dir = normalize(light.position - FragPos);
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = material.ambient * light.ambient;

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = (dot_normal_light * material.diffuse) * light.diffuse;

  float specular_strength = 0.5f;
  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = (material.specular * specular_factor) * light.specular;

  vec3 result = diffuse + ambient + specular;

	FragColor = vec4(result, 1.0f);
}
