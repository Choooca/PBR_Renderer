#include "texture.h"
#include <stb_image.h>
#include <glad/glad.h>
#include <stdexcept>
#include <string>

TextureManager::~TextureManager(){

  for(auto const& [key, value] : m_textures_loaded){
    glDeleteTextures(1, &value);
  }

}

unsigned int TextureManager::GetTexture(const std::string &texture_path){

  std::string complete_path = std::string(TEXTURES_PATH) + "/" + texture_path;

  auto it = m_textures_loaded.find(complete_path); 

  if(it != m_textures_loaded.end())
    return it->second;

  m_textures_loaded[complete_path] = LoadTexture(complete_path);  

  return m_textures_loaded[complete_path];
}

unsigned int TextureManager::LoadTexture(const std::string &texture_path){
  unsigned int texture;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, n_channels;
  unsigned char* data = stbi_load(texture_path.c_str(), &width, &height, &n_channels, 0);

  GLenum format = (texture_path.substr(texture_path.find('.') + 1) == "png") ? GL_RGBA : GL_RGB;
	
  if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		throw std::runtime_error("Failed to load texture : " + texture_path);
	}

	stbi_image_free(data);

  return texture;
}
