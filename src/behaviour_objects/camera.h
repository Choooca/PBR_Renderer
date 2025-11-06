#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <input_handler/input_handler.h>

class Camera {
public :
	glm::mat4 GetViewMatrix() const;
	void Update(const InputHandler* input_manager);

	float speed = 10.0f;

  glm::vec3 m_position = glm::vec3(0, 0, 0.0f);

private :
	
	glm::vec3 fwd = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);

	float cam_sensitivity = 200.0f;

	float pitch, yaw = 270;
};
