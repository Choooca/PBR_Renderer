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
	
	InputHandler* input_handler = new InputHandler(window);
	Camera cam;
	CubeRenderer cube;
	PlaneRenderer plane;

	while (!input_handler->quit) {
		input_handler->Update();
		cam.Update(*input_handler);

		RenderBegin();

		cube.Render(&cam);
		plane.Render(&cam);

		RenderEnd();
	}

	delete input_handler;
	Shader::DestroyAllShader();
	DestroyRender();

	return 0;
}