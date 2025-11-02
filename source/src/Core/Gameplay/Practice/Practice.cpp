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
Shader shaderLight;
Camera camera;
Model model;
Model bulb;
DirLight dirLight;
PointLight pointLight;
glm::mat4 projection;
} // namespace ProgramValues

static Shader *shaderObject = &ProgramValues::shaderObject;
static Shader *shaderLight = &ProgramValues::shaderLight;
static Camera *camera = &ProgramValues::camera;
static Model *model = &ProgramValues::model;
static Model *bulb = &ProgramValues::bulb;
static ProgramValues::DirLight *dirLight = &ProgramValues::dirLight;
static ProgramValues::PointLight *pointLight = &ProgramValues::pointLight;
static glm::mat4 *projection = &ProgramValues::projection;

void Practice::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  { // ProgramValues
    Game *game = Game::getInstance();

    // Shaders
    shaderObject->init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());

    shaderLight->init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/light.glsl").c_str());

    // Models
    model->loadModel(std::string(ASSET_PATH) + "/models/earth_1.glb");
    bulb->loadModel(std::string(ASSET_PATH) +
                    "/models/low_poly_light_bulb.glb");

    // Lights
    dirLight->direction = glm::vec3(0.0f, -5.0f, 0.0f);
    dirLight->ambient = glm::vec3(0.2f);
    dirLight->diffuse = glm::vec3(0.45f);
    dirLight->specular = glm::vec3(0.57f);

    pointLight->position = glm::vec3(1.0f);
    pointLight->constant = 1.0f;
    pointLight->linear = 0.35f;
    pointLight->quadratic = 0.44f;
    pointLight->ambient = glm::vec3(0.2f);
    pointLight->diffuse = glm::vec3(0.45f);
    pointLight->specular = glm::vec3(0.57f);

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
  // 3D Matrices
  shaderObject->setMat4("u_Projection", *projection); // u_Projection of glsl
  shaderObject->setMat4("u_View", camera->getViewMatrix());

  // General Light Property
  // DirLight
  shaderObject->setVec3("dirLight.direction", dirLight->direction);
  shaderObject->setVec3("dirLight.ambient", dirLight->ambient);
  shaderObject->setVec3("dirLight.diffuse", dirLight->diffuse);
  shaderObject->setVec3("dirLight.specular", dirLight->specular);
  // Point Light
  shaderObject->setVec3("pointLight.position", pointLight->position);
  shaderObject->setFloat("pointLight.constant", pointLight->constant);
  shaderObject->setFloat("pointLight.linear", pointLight->linear);
  shaderObject->setFloat("pointLight.quadratic", pointLight->quadratic);
  shaderObject->setVec3("pointLight.ambient", pointLight->ambient);
  shaderObject->setVec3("pointLight.diffuse", pointLight->diffuse);
  shaderObject->setVec3("pointLight.specular", pointLight->specular);

  shaderObject->setVec3("u_ViewPos", camera->position);

  shaderObject->unbind();

  shaderLight->bind();
  // Sync bulb model position to point light position
  pointLight->position = glm::vec3(bulb->transform[3]);
  // 3D Matrices
  shaderLight->setMat4("u_Projection", *projection); // u_Projection of glsl
  shaderLight->setMat4("u_View", camera->getViewMatrix());
  shaderLight->unbind();
}

void Practice::render() {
  shaderObject->bind();
  glEnable(GL_CULL_FACE);
  model->Draw(*shaderObject);
  glDisable(GL_CULL_FACE);
  shaderObject->unbind();

  shaderLight->bind();
  bulb->Draw(*shaderLight);
  shaderLight->unbind();
}
