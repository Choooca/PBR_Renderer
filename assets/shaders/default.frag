#version 330 core
out vec4 FragColor;

struct Material{
  sampler2D diffuse;
  sampler2D specular;
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
in vec2 TexCoords;

//https://www.amazon.com/Mathematics-Programming-Computer-Graphics-Second/dp/1584502770
// http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/

void main()
{
  vec3 normal = normalize(Normal);
  vec3 light_dir = normalize(light.position - FragPos);
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = dot_normal_light * light.diffuse *vec3(texture(material.diffuse, TexCoords));

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = vec3(texture(material.specular, TexCoords)) * specular_factor * light.specular;

  vec3 result = diffuse + ambient + specular;

	FragColor = vec4(result, 1.0f);
}
