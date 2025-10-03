#include <iostream>
#include "renderer/render.h"
#include "renderer/shader.h"
#include "input_handler/input_handler.h"
#include "behaviour_objects/camera.h"

int main(int argc, char *argv[])
{
	RenderInit();
	
	InputHandler* input_handler = new InputHandler(window);
	Shader* shader = Shader::GetShader("default.vert", "default.frag");
	Camera cam;

	while (!input_handler->quit) {
		input_handler->Update();
		cam.Update(*input_handler);

		RenderBegin();

		RenderEnd();
	}

	delete input_handler;
	Shader::DestroyAllShader();
	DestroyRender();

	return 0;
}