#include "shapes_factory.h"
#include "renderer/shapes/blank_cube.h"
#include "renderer/shapes/cube_renderer.h"
#include "renderer/shapes/plane_renderer.h"
#include "renderer/shapes/shape_renderer.h"
#include <memory>

ShapesFactory::~ShapesFactory() { shapes.clear(); };

ShapeRenderer *ShapesFactory::CreateShape(
    SHAPES shape, const std::unique_ptr<AppContext> &context,
    const glm::vec3 &position, const std::string &texture_path) {

  switch (shape) {
  case CUBE:
    shapes.push_back(std::make_unique<CubeRenderer>(context, position,
                                                    texture_path));
    break;
    case BLANK_CUBE:
    shapes.push_back(std::make_unique<BlankCube>(context, position,
                                                 texture_path));
    break;
  case PLANE:
    shapes.push_back(std::make_unique<PlaneRenderer>(
        context, position, texture_path));
    break;
  default:
    shapes.push_back(std::make_unique<CubeRenderer>(context, position,
                                                    texture_path));
    break;
  }

  shapes.back()->InitBuffers();

  return shapes.back().get();
}
