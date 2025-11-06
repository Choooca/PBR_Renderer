#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

struct AppContext;
class ShapeRenderer;

enum SHAPES { CUBE, BLANK_CUBE, PLANE };

class ShapesFactory {

public:
  ShapesFactory() = default;
  ~ShapesFactory();

  ShapeRenderer*
  CreateShape(SHAPES shape, const std::unique_ptr<AppContext> &context,
              const glm::vec3 &position = glm::vec3(0.0f),
              const std::string &texture_path = "debug.png");

  std::vector<std::unique_ptr<ShapeRenderer>> shapes;
};
