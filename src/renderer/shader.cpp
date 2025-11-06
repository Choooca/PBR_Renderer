#include "shader.h"
#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string &shader_name)
{
  std::string vertex_complete_path = std::string(SHADERS_PATH) +  "/" + shader_name + ".vert";
  std::string fragment_complete_path = std::string(SHADERS_PATH) + '/' + shader_name + ".frag";

	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertex_complete_path);
		fShaderFile.open(fragment_complete_path);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("Failed to read shader : " + std::string(e.what()));
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    throw std::runtime_error("Failed to compile vertex shader : " + std::string(infoLog));
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    throw std::runtime_error("Failed to compile fragment shader : " + std::string(infoLog));
	};

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
    throw std::runtime_error("Failed to link shader : " + std::string(infoLog));
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader(){
  glDeleteProgram(m_ID);
}

void Shader::use()
{
	glUseProgram(m_ID);
}
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setColor(const std::string& name, glm::vec4 value) const
{
	glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
  glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
};


std::shared_ptr<Shader> ShaderManager::GetShader(const std::string &shader_name) {

	std::string key = shader_name;

	if (ShaderManager::shader_loaded.find(key) == ShaderManager::shader_loaded.end()) {
		return ShaderManager::shader_loaded[key] = std::make_shared<Shader>(shader_name);
	}

	return ShaderManager::shader_loaded[key];
}


ShaderManager::~ShaderManager(){
  shader_loaded.clear();
}

