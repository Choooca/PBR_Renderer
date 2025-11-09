#version 330 core
out vec4 FragColor;

struct Material{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

// DIRECTIONAL LIGHT
struct DirectionalLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform DirectionalLight directional_light;

//POINT LIGHT (WITH ATTENUATION)
struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};
#define N_POINT_LIGHT 4

#if N_POINT_LIGHT > 0
  uniform PointLight points_lights[N_POINT_LIGHT];
#endif

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
#define N_SPOT_LIGHT 1

#if N_SPOT_LIGHT > 0
  uniform SpotLight spots_lights[N_SPOT_LIGHT];
#endif

uniform Material material;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

//https://www.amazon.com/Mathematics-Programming-Computer-Graphics-Second/dp/1584502770
// http://www.lighthouse3d.com/tutorials/glsl-12-tutorial/the-normal-matrix/

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color);

void main()
{
  vec3 normal = normalize(Normal);
  vec3 view_dir = normalize( - FragPos);
  vec3 diffuse_color = vec3(texture(material.diffuse, TexCoords));
  vec3 specular_color = vec3(texture(material.specular, TexCoords));

  vec3 result = CalculateDirectionalLight(directional_light, normal, view_dir, diffuse_color, specular_color);
 
  #if N_POINT_LIGHT > 0
    for(int i = 0; i < N_POINT_LIGHT ; i++)
      result += CalculatePointLight(points_lights[i], normal, view_dir, diffuse_color, specular_color);
  #endif

  #if N_SPOT_LIGHT > 0   
    for(int i = 0; i < N_SPOT_LIGHT; i++)
      result += CalculateSpotLight(spots_lights[i], normal, view_dir, diffuse_color, specular_color);
  #endif

  FragColor = vec4(result, 1.0f);

};

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color)
{
  vec3 light_dir = normalize(-light.direction);

  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * diffuse_color;

  float diffuse_factor = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = diffuse_factor * light.diffuse * diffuse_color;

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = specular_color * specular_factor * light.specular;

  vec3 result = diffuse + ambient + specular;

	return result;
};

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color){

  float distance = length(light.position - FragPos);
  float attenuation = (1.0f) / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 light_dir = normalize(light.position - FragPos);
  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * diffuse_color;

  float diffuse_factor = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = diffuse_factor * light.diffuse * diffuse_color;

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = specular_color * specular_factor * light.specular;

  vec3 result = (diffuse + ambient + specular) * attenuation;

	return result; 
};


vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 view_dir, vec3 diffuse_color, vec3 specular_color){
  vec3 light_dir = normalize(light.position - FragPos);
  float theta = dot(-light_dir, normalize(light.direction));

  float epsilon = light.inner_cut_off - light.outer_cut_off;
  float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0f, 1.0f);

  vec3 reflect_dir = reflect(-light_dir, normal);

  vec3 ambient = light.ambient * diffuse_color;

  float diffuse_factor = max(dot(light_dir, normal), 0.0f);
  vec3 diffuse = diffuse_factor * light.diffuse * diffuse_color;

  float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  vec3 specular = specular_color * specular_factor * light.specular;

  vec3 result = ambient + (diffuse + specular) * intensity;

	return result;

};
