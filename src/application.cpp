#include "application.h"
#include "behaviour_objects/camera.h"
#include "glm/ext/vector_float3.hpp"
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
  shape_factory->CreateShape(CUBE, m_context);

  ShapeRenderer *plane = shape_factory->CreateShape(PLANE, m_context);

  plane->SetColor({1.0f, 1.0f, 0.0f});
  plane->SetPosition({1.0f, 0.0f, 0.0f});

  ShapeRenderer *blank_cube = shape_factory->CreateShape(BLANK_CUBE, m_context);

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  Light light = Light();
  light.m_position = {7.0F, 7.0F, 7.0F};
  blank_cube->SetPosition(light.m_position);

  light.m_color = {.7f, .3f, 1.0f};

  while (!m_context->GetInputHandler()->quit) {
    m_context->GetInputHandler()->Update();
    camera->Update(m_context->GetInputHandler());

    m_context->GetWindow()->RenderBegin();

    for (auto &s : shape_factory->shapes) {
      s->Render(camera.get(), &light);
    };

    m_context->GetWindow()->RenderEnd();
  }
}
