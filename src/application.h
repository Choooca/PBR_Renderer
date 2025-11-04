#pragma once
#include "renderer/shader.h"
#include <memory>

class Window;
class InputHandler;
class TextureManager;
class ShaderManager;

struct AppContext {

public:
  AppContext();
  ~AppContext();

  Window *GetWindow() const { return m_window.get(); };
  InputHandler *GetInputHandler() const { return m_input_handler.get(); };
  TextureManager *GetTextureManager() const { return m_texture_manager.get(); };
  ShaderManager *GetShaderManager() const { return m_shader_manager.get(); };

private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<InputHandler> m_input_handler;
  std::unique_ptr<TextureManager> m_texture_manager;
  std::unique_ptr<ShaderManager> m_shader_manager;
};

class Application {
public:
  Application();
  ~Application();

  void Run();

private:
  std::unique_ptr<AppContext> m_context;
};
