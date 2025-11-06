#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

class Shader
{

public:

	Shader(const std::string &shader_name);

  ~Shader();

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	void setColor(const std::string& name, glm::vec4 value) const;
  void SetVec3(const std::string& name, glm::vec3 value) const;

private:

	unsigned int m_ID;
};

class ShaderManager{
public:
  
  std::shared_ptr<Shader> GetShader(const std::string &shader_name);

  ~ShaderManager();

private:

	std::unordered_map<std::string, std::shared_ptr<Shader>> shader_loaded;

};
