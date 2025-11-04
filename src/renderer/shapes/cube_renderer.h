#pragma once
#include <behaviour_objects/camera.h>
#include "shape_renderer.h"

class CubeRenderer : public ShapeRenderer {
public:
  
  CubeRenderer(const std::unique_ptr<AppContext> &context,
                const glm::vec3 &position,
                const std::string &texture_path,
                const std::string &shader_name);

  void InitBuffers() override;

protected:
	 
  void Render() override;
};
