#pragma once
#include <SDL.h>
#include <glm/glm.hpp>

class Shader;
class Camera;
class Model;

namespace ProgramValues {
struct Light {
  glm::vec3 position;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};

extern Shader shaderObject;
extern Camera camera;
extern Model model;
extern Light light;
extern glm::mat4 projection;
} // namespace ProgramValues

namespace Practice {
extern void init();
extern void handleInput(SDL_Event &event, SDL_Window *window);
extern void update(const float &deltaTime);
extern void render();
} // namespace Practice
