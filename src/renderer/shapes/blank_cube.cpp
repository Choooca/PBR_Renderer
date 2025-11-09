#include "blank_cube.h"
#include "application.h"
#include "behaviour_objects/camera.h"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"
#include "renderer/shader.h"
#include "renderer/shapes/shape_renderer.h"

static float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f,
    0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,

    -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f,
    0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, 0.5f,
    0.5f,  -0.5f, 0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f, -0.5f,

    -0.5f, 0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,  -0.5f};

BlankCube::BlankCube(const std::unique_ptr<AppContext> &context,
                     const glm::vec3 &position, const std::string &texture_path)
    : ShapeRenderer(context, position, texture_path) {
  m_shader = context->GetShaderManager()->GetShader("light_point");
};

void BlankCube::InitBuffers() {
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void BlankCube::Render(const Camera *cam){
  m_shader->use();

  glm::mat4 projection_matrix = glm::mat4(1.0f);
  projection_matrix =
  glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, .1f, 100.0f);

  glm::mat4 model_mat = glm::translate(glm::mat4(1.0f), m_position);
  model_mat = glm::scale(model_mat, m_scale);

  glBindVertexArray(m_VAO);
  m_shader->setMat4("model", model_mat);
  m_shader->setMat4("projection", projection_matrix);
  m_shader->setMat4("view", cam->GetViewMatrix());

  m_shader->SetVec3("color", m_color);

  glDrawArrays(GL_TRIANGLES, 0, 36); 

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
