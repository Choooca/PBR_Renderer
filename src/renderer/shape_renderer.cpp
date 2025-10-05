#include "shape_renderer.h"
#include "cube_renderer.h"
#include "plane_renderer.h"
#include <errno.h>
#include  <stb_image.h>

ShapeRenderer::ShapeRenderer(const glm::vec3 &position) : m_position(position) {};

std::unique_ptr<ShapeRenderer> ShapeRenderer::Create(SHAPES shape, const glm::vec3& position, std::string texture_path) {
	std::unique_ptr<ShapeRenderer> renderer;

	switch (shape)
	{
	case CUBE:
		renderer = std::make_unique<CubeRenderer>(position);
		break;
	case PLANE:
		renderer = std::make_unique<PlaneRenderer>(position);
		break;
	default:
		return nullptr;
	}

	renderer->InitVariables(texture_path);

	return renderer;
}

void ShapeRenderer::InitVariables(std::string texture_path) {
	InitBuffers();
	try { InitTextures(texture_path); }
	catch (const std::runtime_error& e) { fprintf(stderr, e.what()); }
}

void ShapeRenderer::InitTextures(std::string texture_path) {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nChannels;
	unsigned char* data = stbi_load((std::string(TEXTURES_PATH) + "/" + texture_path).c_str(), &width, &height, &nChannels, 0);

	GLenum format = (texture_path.substr(texture_path.find('.') + 1) == "png") ? GL_RGBA : GL_RGB;

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		throw std::runtime_error("Failed to load texture : " + std::string(TEXTURES_PATH) + "/" + texture_path);
	}

	stbi_image_free(data);
}
