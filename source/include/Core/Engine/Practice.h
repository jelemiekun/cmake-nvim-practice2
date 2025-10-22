#pragma once
#include <SDL.h>

namespace Practice {
extern void handleInput(SDL_Event &event);
extern void update(const float &deltaTime);
extern void render();
} // namespace Practice
