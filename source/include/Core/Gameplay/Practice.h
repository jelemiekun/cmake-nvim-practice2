#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

class Shader;
class Camera;
class Model;

namespace ProgramValues {
extern Shader shaderObject;
extern Camera camera;
extern Model model;
extern glm::mat4 projection;

extern glm::vec3 lightColor;
extern glm::vec3 lightPos;

extern float ambientStrength;
extern float specularStrength;
extern float specularShininess;
} // namespace ProgramValues

namespace Practice {
extern void init();
extern void handleInput(SDL_Event &event, SDL_Window *window);
extern void update(const float &deltaTime);
extern void render();
} // namespace Practice
