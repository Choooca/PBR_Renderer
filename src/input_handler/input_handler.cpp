#include "input_handler.h"

InputHandler::InputHandler(SDL_Window* window) {
	current_time = SDL_GetTicks();
	last_time = 0;
	delta_time = 0;
	quit = false;
	SDL_SetWindowRelativeMouseMode(window, true);
}

void InputHandler::CalculateDeltaTime() {
	current_time = SDL_GetTicks();
	delta_time = (current_time - last_time) / 1000.0f;
	last_time = current_time;
}

void  InputHandler::Update() {
	CalculateDeltaTime();

	SDL_Event event;
	mouse_dx = mouse_dy = 0;
	
	while (SDL_PollEvent(&event)) {

		switch (event.type)
		{
		case SDL_EVENT_MOUSE_MOTION:
			mouse_dx = event.motion.xrel;
			mouse_dy = event.motion.yrel;
			break;
		case SDL_EVENT_QUIT:
			quit = true;
			break;
		case SDL_EVENT_KEY_DOWN:
				if(event.key.key < 128) keys[event.key.key] = true;
			break;
		case SDL_EVENT_KEY_UP:
			if (event.key.key < 128) keys[event.key.key] = false;
			break;
		default:
			break;
		}
	}
}

bool InputHandler::GetKey(int key_code) const {
	return keys[key_code];
}
