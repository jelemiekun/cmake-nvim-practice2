#pragma once
#include <SDL.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/glm.hpp>

class Shader;
class Camera;
class Model;

namespace ProgramValues {
struct DirLight {
  glm::vec3 direction;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};

struct PointLight {
  glm::vec3 position;
  float constant;
  float linear;
  float quadratic;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
};

struct SpotLight {
  float innerCutoff;
  float outerCutoff;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float constant;
  float linear;
  float quadratic;
};

extern Shader sourceShader;
extern Camera *camera;
extern Camera cameraFF;  // Free Fly
extern Camera cameraFPV; // First Person View
extern Camera cameraFV;  // Front View
extern Camera cameraBV;  // Back View
extern Model ship_in_clouds;
extern glm::mat4 projection;
} // namespace ProgramValues

namespace Practice {
extern void init();
extern void handleInput(SDL_Event &event, SDL_Window *window);
extern void update(const float &deltaTime);
extern void render();
extern void free();
} // namespace Practice
