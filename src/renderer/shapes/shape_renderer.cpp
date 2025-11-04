#include "shape_renderer.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <application.h>
#include <renderer/texture.h>
#include <renderer/shader.h>
#include <behaviour_objects/camera.h>

ShapeRenderer::ShapeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position,
                const std::string &texture_path,
                const std::string &shader_name) : m_position(position) {

  m_texture = context->GetTextureManager()->GetTexture(texture_path);
  m_shader = context->GetShaderManager()->GetShader(shader_name);

  InitBuffers();
  }

void ShapeRenderer::RenderLoop(const std::unique_ptr<Camera> &cam){
  m_shader->use();
  
  glm::mat4 projection_matrix = glm::mat4(1.0f);
  projection_matrix =
      glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, .1f, 100.0f);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glBindVertexArray(m_VAO);
  m_shader->setMat4("model", glm::translate(glm::mat4(1.0f), m_position));
  m_shader->setMat4("projection", projection_matrix);
  m_shader->setMat4("view", cam->GetViewMatrix());

  Render();
  
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

ShapeRenderer::~ShapeRenderer(){
  if(m_VAO) glDeleteVertexArrays(1, &m_VAO);
  if(m_VBO) glDeleteBuffers(1, &m_VBO);
  if(m_EBO) glDeleteBuffers(1, &m_EBO);
}
