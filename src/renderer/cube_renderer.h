#pragma once
#include <behaviour_objects/camera.h>
#include "shader.h"
#include "shape_renderer.h"

class CubeRenderer : public ShapeRenderer {
public:
	CubeRenderer();
	void Render(Camera* cam) override;
};
