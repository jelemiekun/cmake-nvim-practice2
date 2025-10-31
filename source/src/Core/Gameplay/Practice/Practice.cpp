#include "Practice.h"
#include "Camera.h"
#include "Game.h"
#include "Model.h"
#include "Shader.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <spdlog/spdlog.h>
#include <string>

namespace ProgramValues {
Shader shaderObject;
Camera camera;
Model model;
DirLight dirLight;
glm::mat4 projection;
} // namespace ProgramValues

static Shader *shaderObject = &ProgramValues::shaderObject;
static Camera *camera = &ProgramValues::camera;
static Model *model = &ProgramValues::model;
static ProgramValues::DirLight *dirLight = &ProgramValues::dirLight;
static glm::mat4 *projection = &ProgramValues::projection;

void Practice::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  { // ProgramValues
    Game *game = Game::getInstance();

    shaderObject->init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
    model->loadModel(std::string(ASSET_PATH) + "/models/earth_1.glb");

    dirLight->direction = glm::vec3(0.0f, 5.0f, 0.0f);
    dirLight->ambient = glm::vec3(0.2f);
    dirLight->diffuse = glm::vec3(0.45f);
    dirLight->specular = glm::vec3(0.57f);

    *projection = glm::perspective(glm::radians(60.0f),
                                   (float)game->m_WindowWidth /
                                       (float)game->m_WindowHeight,
                                   0.001f, 1000.0f);
  }
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  camera->processKeyboard(event, window);
  camera->processMouseMotion(event);

  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_EQUALS:
      model->transform =
          glm::scale(model->transform, glm::vec3(1.5f, 1.5f, 1.5f));
      break;
    case SDLK_MINUS:
      model->transform =
          glm::scale(model->transform, glm::vec3(0.5f, 0.5f, 0.5f));
      break;
    }
  }
}

void Practice::update(const float &deltaTime) {
  camera->update();

  shaderObject->bind();
  model->update(*shaderObject); // u_Model of glsl
  // 3D Matrices
  shaderObject->setMat4("u_Projection", *projection); // u_Projection of glsl
  shaderObject->setMat4("u_View", camera->getViewMatrix());

  // General Light Property
  shaderObject->setVec3("dirLight.direction", dirLight->direction);
  shaderObject->setVec3("dirLight.ambient", dirLight->ambient);
  shaderObject->setVec3("dirLight.diffuse", dirLight->diffuse);
  shaderObject->setVec3("dirLight.specular", dirLight->specular);

  shaderObject->setVec3("u_ViewPos", camera->position);

  shaderObject->unbind();
}

void Practice::render() {
  shaderObject->bind();
  glEnable(GL_CULL_FACE);
  model->Draw(*shaderObject);
  glDisable(GL_CULL_FACE);
  shaderObject->unbind();
}
