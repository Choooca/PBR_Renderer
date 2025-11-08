#include "texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>
#include <string>

TextureManager::~TextureManager() {

  for (auto const &[key, value] : m_textures_loaded) {
    glDeleteTextures(1, &value);
  }
}

unsigned int TextureManager::GetTexture(const std::string &texture_path) {

  std::string complete_path = std::string(TEXTURES_PATH) + "/" + texture_path;

  auto it = m_textures_loaded.find(complete_path);

  if (it != m_textures_loaded.end())
    return it->second;

  m_textures_loaded[complete_path] = LoadTexture(complete_path);

  return m_textures_loaded[complete_path];
}

unsigned int TextureManager::LoadTexture(const std::string &texture_path) {
  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, n_channels;
  unsigned char *data =
      stbi_load(texture_path.c_str(), &width, &height, &n_channels, 0);



  if (!data) {
    std::string error_msg = "Failed to load texture: " + texture_path;
    const char *reason = stbi_failure_reason();
    if (reason) {
      error_msg += " - Reason: " + std::string(reason);
    }
    throw std::runtime_error(error_msg);
  }

  GLenum format;
  switch (n_channels) {
  case 1:
    format = GL_RED;
    break;
  case 3:
    format = GL_RGB;
    break;
  case 4:
    format = GL_RGBA;
    break;
  default:
    stbi_image_free(data);
    throw std::runtime_error("Unsupported channel count");
  }

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  return texture;
}
