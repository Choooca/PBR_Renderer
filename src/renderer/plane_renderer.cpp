#include "plane_renderer.h"

float vertices[] = {
	// positions        // texture coords
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
};
static unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

void PlaneRenderer::InitVariables() {
	m_shader = Shader::GetShader("default.vert", "default.frag");

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

PlaneRenderer::PlaneRenderer(const glm::vec3 &m_position) : ShapeRenderer(m_position) {}

PlaneRenderer::~PlaneRenderer() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

void PlaneRenderer::Render(const std::unique_ptr<Camera>& cam) {
	m_shader->use();

	glm::mat4 projection_matrix = glm::mat4(1.0f);
	projection_matrix = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, .1f, 100.0f);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	m_shader->setMat4("model", glm::mat4(1.0f));
	m_shader->setMat4("projection", projection_matrix);
	m_shader->setMat4("view", cam->GetViewMatrix());

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}