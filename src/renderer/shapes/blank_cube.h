#pragma once
#include <renderer/shapes/shape_renderer.h>

class BlankCube : public ShapeRenderer {

public:
  BlankCube(const std::unique_ptr<AppContext> &context,
            const glm::vec3 &position, const std::string &texture_path);

  void InitBuffers() override;

  void Render(const Camera *cam, const Light *light) override;
};
