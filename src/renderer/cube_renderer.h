#include <behaviour_objects/camera.h>
#include "shader.h"

class CubeRenderer{
public:
	CubeRenderer();
	void Render(Camera* cam);

private:
	Shader* shader;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};
