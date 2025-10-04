#pragma once
#include <behaviour_objects/camera.h>
#include <glm/glm.hpp>
#include "shader.h"

enum SHAPES {
	CUBE,
	PLANE
};

class ShapeRenderer {
public:
	ShapeRenderer(const glm::vec3 &position = glm::vec3(0.0f));
	virtual void Render(const std::unique_ptr<Camera>& cam) = 0;
	virtual ~ShapeRenderer() = default;

	static std::unique_ptr<ShapeRenderer> Create(SHAPES shape, const glm::vec3& position = glm::vec3(0.0f));
	virtual void InitVariables() = 0;
protected:
	Shader* m_shader;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	glm::vec3 m_position;

};
