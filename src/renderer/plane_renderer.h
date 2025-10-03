#pragma once
#include "shape_renderer.h"

class PlaneRenderer : public ShapeRenderer {
public:
	PlaneRenderer();
	void Render(Camera* cam) override;
};