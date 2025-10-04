#include "shape_renderer.h"
#include "cube_renderer.h"
#include "plane_renderer.h"

ShapeRenderer::ShapeRenderer(const glm::vec3 &position) : m_position(position) {};

std::unique_ptr<ShapeRenderer> ShapeRenderer::Create(SHAPES shape, const glm::vec3& position) {
	std::unique_ptr<ShapeRenderer> renderer;

	switch (shape)
	{
	case CUBE:
		renderer = std::make_unique<CubeRenderer>(position);
		break;
	case PLANE:
		renderer = std::make_unique<PlaneRenderer>(position);
		break;
	default:
		return nullptr;
	}

	renderer->InitVariables();

	return renderer;
}