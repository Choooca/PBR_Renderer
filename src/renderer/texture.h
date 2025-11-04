#pragma once
#include <map>
#include <string>

class TextureManager{

public:

  TextureManager() = default;
  ~TextureManager();
  
  unsigned int GetTexture(const std::string &texture_path);

private:

  std::map<std::string, unsigned int> m_textures_loaded;
  
  unsigned int LoadTexture( const std::string &texture_path);
};
