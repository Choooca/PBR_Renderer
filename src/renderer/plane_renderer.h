#pragma once
#include "shape_renderer.h"

class PlaneRenderer : public ShapeRenderer {
public:
	PlaneRenderer(const glm::vec3 &m_position = glm::vec3(0.0f));
	~PlaneRenderer();
	void Render(const std::unique_ptr<Camera>& cam) override;
protected:
	void InitVariables() override;
};