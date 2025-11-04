#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>

class Camera;
class Shader;
class ShaderManager;
struct AppContext;

class ShapeRenderer {
public:

  ShapeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position = glm::vec3(0.0f),
                const std::string &texture_path = "debug.png",
                const std::string &shader_name = "default");

  virtual ~ShapeRenderer();

  virtual void InitBuffers() {};

  void RenderLoop(const std::unique_ptr<Camera> &cam);

protected:

  std::shared_ptr<Shader> m_shader;
  unsigned int m_texture;

  unsigned int m_VAO = 0;
  unsigned int m_VBO = 0;
  unsigned int m_EBO = 0;

  glm::vec3 m_position;
  
  virtual void Render() {};

};
