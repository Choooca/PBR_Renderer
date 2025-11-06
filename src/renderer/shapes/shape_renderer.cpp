#include "shape_renderer.h"
#include <application.h>
#include <behaviour_objects/camera.h>
#include <glad/glad.h>
#include <renderer/shader.h>
#include <renderer/texture.h>
#include <stb_image.h>

ShapeRenderer::ShapeRenderer(const std::unique_ptr<AppContext> &context,
                             const glm::vec3 &position,
                             const std::string &texture_path)
    : m_position(position) {

  m_texture = context->GetTextureManager()->GetTexture(texture_path);
}

void ShapeRenderer::SetTexture(const std::string &texture_path,
                               TextureManager *texture_manager) {
  m_texture = texture_manager->GetTexture(texture_path);
}

void ShapeRenderer::SetTexture(unsigned int texture) { m_texture = texture; };

ShapeRenderer::~ShapeRenderer() {
  if (m_VAO)
    glDeleteVertexArrays(1, &m_VAO);
  if (m_VBO)
    glDeleteBuffers(1, &m_VBO);
  if (m_EBO)
    glDeleteBuffers(1, &m_EBO);
}
