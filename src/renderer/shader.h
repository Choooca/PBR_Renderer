#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	static std::unordered_map<std::string, Shader*> shader_loaded;

	static Shader* GetShader(std::string vertexPath, std::string fragmentPath);
	static void DestroyAllShader();

	unsigned int ID;

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	void setColor(const std::string& name, glm::vec4 value) const;
private:
	Shader(std::string vertexPath, std::string fragmentPath);
};
