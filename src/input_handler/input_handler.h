#pragma once
#include <SDL3/SDL.h>

class InputHandler {
public:
	InputHandler(SDL_Window* window);
	void Update();
	bool GetKey(int key_code) const;

	bool quit = false;
	float delta_time = 0;

	float mouse_dx, mouse_dy;

private:
	void CalculateDeltaTime();

	float current_time;
	float last_time;

	bool keys[1000] = { false };
};
	



