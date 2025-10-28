#pragma once
#include <SDL.h>

namespace Practice {
extern void init();
extern void handleInput(SDL_Event &event, SDL_Window *window);
extern void update(const float &deltaTime);
extern void render();
} // namespace Practice
