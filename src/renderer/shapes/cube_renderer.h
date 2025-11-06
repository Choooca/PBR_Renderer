#pragma once
#include <behaviour_objects/camera.h>
#include "shape_renderer.h"

class CubeRenderer : public ShapeRenderer {
public:
  
  CubeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position,
                const std::string &texture_path);

  void InitBuffers() override;

  void Render(const Camera *cam, const Light *light) override;

};
