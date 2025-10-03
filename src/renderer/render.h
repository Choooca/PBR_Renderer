#pragma once
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>

extern SDL_Window* window;
extern SDL_GLContext context;

void RenderInit();
void RenderBegin();
void RenderEnd();

void DestroyRender();

