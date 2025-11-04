#include "application.h"
#include "behaviour_objects/camera.h"
#include <renderer/shapes/shape_renderer.h>
#include <input_handler/input_handler.h>
#include <renderer/shapes/shapes_factory.h>
#include <renderer/texture.h>
#include <renderer/window.h>
#include <memory>

AppContext::AppContext(){
  m_window = std::make_unique<Window>("PBR_Renderer", 800, 600);
  m_input_handler = std::make_unique<InputHandler>(m_window->GetWindow());
  m_texture_manager = std::make_unique<TextureManager>();
  m_shader_manager = std::make_unique<ShaderManager>();
}

AppContext::~AppContext() {}

Application::Application() {
 m_context = std::make_unique<AppContext>(); 
};

Application::~Application() {};

void Application::Run(){
  
  std::unique_ptr<ShapesFactory> shape_factory = std::make_unique<ShapesFactory>();
  shape_factory->CreateShape(CUBE, m_context);
  shape_factory->CreateShape(PLANE, m_context);

  std::unique_ptr<Camera> camera = std::make_unique<Camera>();

  while(!m_context->GetInputHandler()->quit)
  {
    m_context->GetInputHandler()->Update();
    camera->Update(m_context->GetInputHandler());

    m_context->GetWindow()->RenderBegin();

    for(auto &s : shape_factory->shapes){
      s->RenderLoop(camera);
    };

    m_context->GetWindow()->RenderEnd();
  } 

}
