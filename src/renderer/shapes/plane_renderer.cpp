#include "plane_renderer.h"
#include "application.h"
#include <behaviour_objects/camera.h>
#include <glad/glad.h>
#include <renderer/shader.h>

static float vertices[] = {
    // positions        // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // top left
};
static unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

PlaneRenderer::PlaneRenderer(const std::unique_ptr<AppContext> &context,
                             const glm::vec3 &position,
                             const std::string &texture_path)
    : ShapeRenderer(context, position, texture_path) {
  m_shader = context->GetShaderManager()->GetShader("default");
}

void PlaneRenderer::InitBuffers() {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void PlaneRenderer::Render(const Camera *cam, const Light *light) {

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

  m_shader->SetVec3("light_color", light->m_color);
  m_shader->SetVec3("object_color", m_color);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
