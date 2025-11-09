#include "application.h"
#include "behaviour_objects/camera.h"
#include "glm/ext/vector_float3.hpp"
#include "glm/trigonometric.hpp"
#include <cmath>
#include <ctime>
#include <input_handler/input_handler.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <renderer/shapes/shape_renderer.h>
#include <renderer/shapes/shapes_factory.h>
#include <renderer/texture.h>
#include <renderer/window.h>

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

  Light light = Light();
  light.m_position = {2.0F, 3.0F, 1.0F};
  light.m_color = {1.0f, 1.0f, 1.0f};

  ShapeRenderer *blank_cube = shape_factory->CreateShape(BLANK_CUBE, m_context);
  blank_cube->m_position = light.m_position;
  blank_cube->m_scale = {.2f, .2f, .2f};

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  std::shared_ptr<Shader> default_shader =
      m_context->GetShaderManager()->GetShader("default");

  while (!m_context->GetInputHandler()->quit) {
    m_context->GetInputHandler()->Update();

    camera->Update(m_context->GetInputHandler());

    default_shader->use();
    default_shader->SetVec3("light.ambient", {0.2f, 0.2f, 0.2f});
    default_shader->SetVec3("light.diffuse", {0.5f, 0.5f, 0.5f});
    default_shader->SetVec3("light.specular", {1.0f, 1.0f, 1.0f});

    /* // Point Light (infinite
     default_shader->SetVec3("light.position",
     strength) (camera->GetViewMatrix() *
                              glm::vec4(glm::vec3(light.m_position), 1.0f)));
      blank_cube->m_position = light.m_position;
    */

    /* // Light Direction
    default_shader->SetVec3("light.direction", {-0.2f, -1.0f, -0.3f});
    blank_cube->m_position = glm::vec3(-0.2f, -1.0f, -0.3f) * -10.0f;
    */

    /* // Point Light (With attenuation)
    default_shader->SetVec3("light.position", // Point Light (with attenuation)
                            (camera->GetViewMatrix() *
                             glm::vec4(glm::vec3(light.m_position), 1.0f)));
    default_shader->SetFloat("light.constant", 1.0f);
    default_shader->SetFloat("light.linear", 0.09f);
    default_shader->SetFloat("light.quadratic", 0.032f);

    blank_cube->m_position = light.m_position;
    */

    default_shader->SetVec3("light.position", {0.0f, 0.0f, 0.0f});
    default_shader->SetVec3("light.direction", {0.0f, 0.0f, -1.0f});
    default_shader->SetFloat("light.inner_cut_off", glm::cos(glm::radians(12.5f)));
    default_shader->SetFloat("light.outer_cut_off", glm::cos(glm::radians(27.5f)));


    m_context->GetWindow()->RenderBegin();

    for (auto &s : shape_factory->shapes) {
      s->Render(camera.get(), &light);
    };

    m_context->GetWindow()->RenderEnd();
  }
}
