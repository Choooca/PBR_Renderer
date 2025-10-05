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

	static std::unique_ptr<ShapeRenderer> Create(SHAPES shape, const glm::vec3& position = glm::vec3(0.0f), std::string texture_path = "debug.png");
	virtual void InitVariables(std::string texture_path = "debug.png");
protected:
	Shader* m_shader;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	unsigned int m_texture;

	glm::vec3 m_position;

	virtual void InitBuffers() = 0;
	virtual void InitTextures(std::string texture_path);
	
};
