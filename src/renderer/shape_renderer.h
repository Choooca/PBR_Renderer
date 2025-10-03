#pragma once
#include <behaviour_objects/camera.h>
#include "shader.h"

class ShapeRenderer {
public:
	virtual void Render(Camera* cam) = 0;
	virtual ~ShapeRenderer() = default;
protected:
	Shader* shader;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};
