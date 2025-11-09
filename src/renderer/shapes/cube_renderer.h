#pragma once
#include <behaviour_objects/camera.h>
#include "shape_renderer.h"

class CubeRenderer : public ShapeRenderer {
public:
  
  CubeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position,
                const std::string &texture_path);

  void InitBuffers() override;

  void Render(const Camera *cam) override;

private:

  unsigned int m_diffuse_map = 0;
  unsigned int m_specular_map = 0;
};
