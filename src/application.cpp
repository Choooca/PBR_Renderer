#include "application.h"
#include "behaviour_objects/camera.h"
#include "glm/ext/vector_float3.hpp"
#include <cmath>
#include <input_handler/input_handler.h>
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

  ShapeRenderer *cube = shape_factory->CreateShape(CUBE, m_context);
  cube->m_color = {1.0f, 0.5f, 0.31f};
  cube->m_scale = {20.0f, 1.5f, 20.0f};

  Light light = Light();
  light.m_position = {2.0F, 3.0F, 1.0F};
  light.m_color = {1.0f, 1.0f, 1.0f};

  ShapeRenderer *blank_cube = shape_factory->CreateShape(BLANK_CUBE, m_context);
  blank_cube->m_position = light.m_position;

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  std::shared_ptr<Shader> default_shader =
      m_context->GetShaderManager()->GetShader("default");

  float count = 0;

  while (!m_context->GetInputHandler()->quit) {
    m_context->GetInputHandler()->Update();
    
    camera->Update(m_context->GetInputHandler());

    count += m_context->GetInputHandler()->delta_time;
    blank_cube->m_position = light.m_position;

    light.m_position.x = cos(count) * 10;
    light.m_position.z = sin(count) * 10;

    m_context->GetWindow()->RenderBegin();

    for (auto &s : shape_factory->shapes) {
      s->Render(camera.get(), &light);
    };

    m_context->GetWindow()->RenderEnd();
  }
}
