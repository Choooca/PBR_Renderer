#include "application.h"
#include "behaviour_objects/camera.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include <ctime>
#include <input_handler/input_handler.h>
#include <math.h>
#include <memory>
#include <renderer/shapes/shape_renderer.h>
#include <renderer/shapes/shapes_factory.h>
#include <renderer/texture.h>
#include <renderer/window.h>
#include <string>

AppContext::AppContext() {
  m_window = std::make_unique<Window>("PBR_Renderer", 800, 600);
  m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
  m_texture_manager = std::make_unique<TextureManager>();
  m_shader_manager = std::make_unique<ShaderManager>();
}

AppContext::~AppContext() {}

Application::Application() { m_context = std::make_unique<AppContext>(); };

Application::~Application() {};

void Application::Run() {

  std::unique_ptr<ShapesFactory> shape_factory =
      std::make_unique<ShapesFactory>();

  glm::vec3 cube_positions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

  for (int i = 0; i < 10; i++) {
    ShapeRenderer *cube = shape_factory->CreateShape(CUBE, m_context);
    std::srand(std::time({}) * i);
    int rand = std::rand();
    cube->m_position = cube_positions[i];
    cube->m_rotation_degrees = glm::vec3(rand, rand * 213, rand - 280);
  }

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  std::shared_ptr<Shader> default_shader =
      m_context->GetShaderManager()->GetShader("default");

  glm::vec3 point_light_positions[] = {
      glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(2.3f, -3.3f, -4.0f),
      glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.0f, 0.0f, -3.0f)};

  glm::vec3 point_light_color[] = {
      glm::vec3(1.0f, 0.0f, 0.2f), glm::vec3(0.2f, 0.0f, 1.0f),
      glm::vec3(0.0f, 0.3f, 1.f), glm::vec3(.3f, .2f, 1.0f)};

  for (int i = 0; i < 4; i++) {
    ShapeRenderer *shape = shape_factory->CreateShape(BLANK_CUBE, m_context);
    shape->m_position = point_light_positions[i];
    shape->m_scale = {0.2f, 0.2f, 0.2f};
    shape->m_color = point_light_color[i];
  }

  while (!m_context->GetInputHandler()->quit) {
    m_context->GetInputHandler()->Update();

    camera->Update(m_context->GetInputHandler());

    default_shader->use();

    for (int i = 0; i < 4; i++) {
      std::string path = "points_lights[" + std::to_string(i) + "]."; 

      default_shader->SetVec3(path + "position", point_light_positions[i]);
      default_shader->SetVec3(path + "ambient", point_light_color[i] * .1f);
      default_shader->SetVec3(path + "diffuse", point_light_color[i]);
      default_shader->SetVec3(path + "specular", {1.0f, 1.0f, 1.0f});
      default_shader->SetFloat(path + "constant", 1.0f);
      default_shader->SetFloat(path + "linear", 0.09f);
      default_shader->SetFloat(path + "quadratic", 0.032f);
    }

    default_shader->SetVec3("spots_lights[0].position", {0.0f, 0.0f, 0.0f});
    default_shader->SetVec3("spots_lights[0].direction", {0.0f, 0.0f, -1.0f});
    default_shader->SetVec3("spots_lights[0].ambient", {0.0f, .1f, 0.0f});
    default_shader->SetVec3("spots_lights[0].diffuse", {0.0f, 1.f, 0.0f});
    default_shader->SetVec3("spots_lights[0].specular", {1.0f, 1.0f, 1.0f});
    default_shader->SetFloat("spots_lights[0].inner_cut_off", glm::cos(glm::radians(12.5f)));
    default_shader->SetFloat("spots_lights[0].outer_cut_off", glm::cos(glm::radians(20.0f)));
    
    default_shader->SetVec3("directional_light.direction", {1.0f, 0.0f, 1.0f});
    default_shader->SetVec3("directional_light.ambient", {0.2f, 0.2f, 0.2f});
    default_shader->SetVec3("directional_light.diffuse", {0.5f, 0.5f, 0.5f});
    default_shader->SetVec3("directional_light.specular", {1.0f, 1.0f, 1.0f});

    m_context->GetWindow()->RenderBegin();

    for (auto &s : shape_factory->shapes) {
      s->Render(camera.get());
    };

    m_context->GetWindow()->RenderEnd();
  }
}
