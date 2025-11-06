#include "camera.h"
#include <algorithm>

void Camera::Update(const InputHandler *input_handler) {
	if (input_handler->GetKey(SDLK_Z))
		m_position += fwd * speed * input_handler->delta_time;
	if(input_handler->GetKey(SDLK_S))
		m_position -= fwd * speed * input_handler->delta_time;
	if (input_handler->GetKey(SDLK_Q))
		m_position -= glm::normalize(glm::cross(fwd, up)) * speed * input_handler->delta_time;
	if (input_handler->GetKey(SDLK_D))
		m_position += glm::normalize(glm::cross(fwd, up)) * speed * input_handler->delta_time;

	yaw += input_handler->mouse_dx * cam_sensitivity * input_handler->delta_time;
	pitch -= input_handler->mouse_dy * cam_sensitivity * input_handler->delta_time;

	pitch = std::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	fwd = glm::normalize(dir);
}

glm::mat4 Camera::GetViewMatrix() const {
	return  glm::lookAt(m_position, m_position + fwd, up);
}
