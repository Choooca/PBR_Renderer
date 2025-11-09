#version 330 core
out vec4 FragColor;

struct Material{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

/* POINT LIGHT (INFINITE STRENGH)
struct Light {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform Light light;
*/
/* DIRECTIONAL LIGHT
struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform DirLight light;
*/

/* POINT LIGHT (WITH ATTENUATION)
struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};
uniform PointLight light;
*/

// SPOT LIGHT 
struct SpotLight {
  vec3 position;
  vec3 direction;
  float inner_cut_off;
  float outer_cut_off;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform SpotLight light;

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
  
  vec3 light_dir = normalize(light.position - FragPos);
  float theta = dot(-light_dir, normalize(light.direction));

  float epsilon = light.inner_cut_off - light.outer_cut_off;
  float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0f, 1.0f);

  vec3 normal = normalize(Normal);   
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = dot_normal_light * light.diffuse *vec3(texture(material.diffuse, TexCoords));

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = vec3(texture(material.specular, TexCoords)) * specular_factor * light.specular;

  vec3 result = ambient + (diffuse + specular) * intensity;

	FragColor = vec4(result, 1.0f);

  /* // POINT LIGHT (WITH ATTENUATION)
  float distance = length(light.position - FragPos);
  float attenuation = (1.0f) / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 normal = normalize(Normal);
  vec3 light_dir = normalize(light.position - FragPos);
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = dot_normal_light * light.diffuse *vec3(texture(material.diffuse, TexCoords));

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = vec3(texture(material.specular, TexCoords)) * specular_factor * light.specular;

  vec3 result = (diffuse + ambient + specular) * attenuation;

	FragColor = vec4(result, 1.0f);
  */
  
 
  /* // CALCULATION FOR DIRECTIONAL LIGHT
  vec3 light_dir = normalize(-light.direction);
  vec3 normal = normalize(Normal);
  vec3 view_dir = normalize( - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

  float dot_normal_light = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = dot_normal_light * light.diffuse *vec3(texture(material.diffuse, TexCoords));

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = vec3(texture(material.specular, TexCoords)) * specular_factor * light.specular;

  vec3 result = diffuse + ambient + specular;

	FragColor = vec4(result, 1.0f);
  */

  /* CALCULATION FOR LIGHT POINT (INFINITE STRENGTH)
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
  */
}
