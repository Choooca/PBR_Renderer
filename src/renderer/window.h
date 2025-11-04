#pragma once
#include "SDL3/SDL_video.h"

class Window {
public:
  
  Window(const char* title, int height, int width);
  ~Window();

  inline SDL_Window* GetWindow() { return m_window; };
  inline SDL_GLContext* GetContext() { return &m_context; };

  void RenderBegin();
  void RenderEnd();

private:
  SDL_Window *m_window;
  SDL_GLContext m_context;

  int m_height, m_width;
};

