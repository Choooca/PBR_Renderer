#include "window.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL_init.h>
#include "glad/glad.h"
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar *msg, const void *data) {
  const char *_source;
  const char *_type;
  const char *_severity;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    _source = "API";
    break;

  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    _source = "WINDOW SYSTEM";
    break;

  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    _source = "SHADER COMPILER";
    break;

  case GL_DEBUG_SOURCE_THIRD_PARTY:
    _source = "THIRD PARTY";
    break;

  case GL_DEBUG_SOURCE_APPLICATION:
    _source = "APPLICATION";
    break;

  case GL_DEBUG_SOURCE_OTHER:
    _source = "UNKNOWN";
    break;

  default:
    _source = "UNKNOWN";
    break;
  }

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    _type = "ERROR";
    break;

  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    _type = "DEPRECATED BEHAVIOR";
    break;

  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    _type = "UDEFINED BEHAVIOR";
    break;

  case GL_DEBUG_TYPE_PORTABILITY:
    _type = "PORTABILITY";
    break;

  case GL_DEBUG_TYPE_PERFORMANCE:
    _type = "PERFORMANCE";
    break;

  case GL_DEBUG_TYPE_OTHER:
    _type = "OTHER";
    break;

  case GL_DEBUG_TYPE_MARKER:
    _type = "MARKER";
    break;

  default:
    _type = "UNKNOWN";
    break;
  }

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    _severity = "HIGH";
    break;

  case GL_DEBUG_SEVERITY_MEDIUM:
    _severity = "MEDIUM";
    break;

  case GL_DEBUG_SEVERITY_LOW:
    _severity = "LOW";
    break;
  default:
    _severity = "UNKNOWN";
    break;
  }

  printf("%d: %s of %s severity, raised from %s: %s\n", id, _type, _severity,
         _source, msg);
}

Window::Window(const char *title, int height, int width) : m_height(height), m_width(width) {

  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  m_window = SDL_CreateWindow(title, m_height, m_width, SDL_WINDOW_OPENGL);

  if (!m_window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window : %s\n",
                 SDL_GetError());
    return;
  }

  m_context = SDL_GL_CreateContext(m_window);

  if (!m_context) {
    fprintf(stderr, "Failed to create context : %s \n", SDL_GetError());
    SDL_DestroyWindow(m_window);
    return;
  }

  SDL_GL_MakeCurrent(m_window, m_context);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    fprintf(stderr, "Failed to initialize glad \n");
    SDL_GL_DestroyContext(m_context);
    SDL_DestroyWindow(m_window);
    return;
  }

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(GLDebugMessageCallback, NULL);

  glEnable(GL_DEPTH_TEST);

  stbi_set_flip_vertically_on_load(true);
}

Window::~Window() {
  SDL_GL_DestroyContext(m_context);
  SDL_DestroyWindow(m_window);
};

void Window::RenderBegin() {
  glViewport(0, 0, 800, 600);
  glClearColor(.1f, .1f, .1f, 1.f);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Window::RenderEnd(){
  SDL_GL_SwapWindow(m_window);
}
