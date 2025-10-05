#include <iostream>
#include "renderer/render.h"
#include "renderer/shader.h"
#include "input_handler/input_handler.h"
#include "behaviour_objects/camera.h"
#include "renderer/cube_renderer.h"
#include "renderer/plane_renderer.h"

int main(int argc, char *argv[])
{
	RenderInit();
	
	std::unique_ptr<InputHandler> input_handler = std::make_unique<InputHandler>(window);
	std::unique_ptr<Camera> cam = std::make_unique<Camera>();
	std::unique_ptr<ShapeRenderer> cube = ShapeRenderer::Create(SHAPES::CUBE, glm::vec3(2.0f), "wood.jpg");
	std::unique_ptr<ShapeRenderer> plane = ShapeRenderer::Create(SHAPES::PLANE);

	while (!input_handler->quit) {
		input_handler->Update();
		cam->Update(*input_handler);

		RenderBegin();

		cube->Render(cam);
		plane->Render(cam);

		RenderEnd();
	}

	Shader::DestroyAllShader();
	DestroyRender();

	return 0;
}