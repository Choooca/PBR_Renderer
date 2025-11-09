#pragma once
#include "glm/ext/vector_float3.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <string>

class Camera;
class Shader;
class ShaderManager;
struct AppContext;
class TextureManager;

class ShapeRenderer {
public:
  ShapeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position = glm::vec3(0.0f),
                const std::string &texture_path = "debug.png");

  virtual ~ShapeRenderer();

  virtual void InitBuffers() {};

  virtual void Render(const Camera *cam) {};

  void SetTexture(const std::string &texture_path,
                  TextureManager *texture_manager);
  void SetTexture(unsigned int texture);

  glm::vec3 m_color = {1.0f, 1.0f, 1.0f};
  glm::vec3 m_position = {0.0f, 0.0f, 0.0f}; 
  glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
  glm::vec3 m_rotation_degrees = {0.0f, 0.0f, 0.0f};

protected:
  std::shared_ptr<Shader> m_shader;
  unsigned int m_texture;
 
  unsigned int m_VAO = 0;
  unsigned int m_VBO = 0;
  unsigned int m_EBO = 0;
 

};
