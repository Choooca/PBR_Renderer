#pragma once
#include <behaviour_objects/camera.h>
#include "shader.h"
#include "shape_renderer.h"

class CubeRenderer : public ShapeRenderer {
public:
	CubeRenderer(const glm::vec3 & position = glm::vec3(0.0f));
	~CubeRenderer();

	void Render(const std::unique_ptr<Camera>& cam) override;
	void InitVariables(std::string texture_path = "debug.png") override;
protected:
	void InitBuffers() override;
};
