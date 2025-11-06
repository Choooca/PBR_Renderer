#pragma once
#include "glm/ext/vector_float3.hpp"
#include "renderer/light/light.h"
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

  virtual void Render(const Camera *cam, const Light *light) {};

  void SetTexture(const std::string &texture_path,
                  TextureManager *texture_manager);
  void SetTexture(unsigned int texture);

  void SetColor(const glm::vec3& color) {m_color = color;};

  void SetPosition(const glm::vec3 &position) { m_position = position; };
  glm::vec3 GetPosition() { return m_position; };

protected:
  std::shared_ptr<Shader> m_shader;
  unsigned int m_texture;

  glm::vec3 m_color = {1.0f, 1.0f, 1.0f};

  unsigned int m_VAO = 0;
  unsigned int m_VBO = 0;
  unsigned int m_EBO = 0;

  glm::vec3 m_position; 
};
