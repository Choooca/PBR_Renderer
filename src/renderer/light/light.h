#pragma once
#include "glm/ext/vector_float3.hpp"

class Light{

public:

  glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
  glm::vec3 m_color = {1.0f,1.0f, 1.0f};

  float m_ambient_strength = .1f;
};
