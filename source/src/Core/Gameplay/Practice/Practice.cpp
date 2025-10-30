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

Shader ProgramValues::shaderObject;
Camera ProgramValues::camera;
Model ProgramValues::model;
glm::mat4 ProgramValues::projection;
glm::vec3 ProgramValues::lightColor;
float ProgramValues::ambientStrength = 0.2f;
glm::vec3 ProgramValues::lightPos(0.0f, 10.0f, 0.0f);

static Shader *shaderObject = &ProgramValues::shaderObject;
static Camera *camera = &ProgramValues::camera;
static Model *model = &ProgramValues::model;
static glm::mat4 *projection = &ProgramValues::projection;
static glm::vec3 *lightColor = &ProgramValues::lightColor;
static float *ambientStrength = &ProgramValues::ambientStrength;
static glm::vec3 *lightPos = &ProgramValues::lightPos;

void Practice::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  shaderObject->init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  model->loadModel(std::string(ASSET_PATH) + "/models/earth_1.glb");

  Game *game = Game::getInstance();
  *projection =
      glm::perspective(glm::radians(60.0f),
                       (float)game->m_WindowWidth / (float)game->m_WindowHeight,
                       0.001f, 1000.0f);

  *lightColor = glm::vec3(1.0f);
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
  model->update(*shaderObject);                       // u_Model of glsl
  shaderObject->setMat4("u_Projection", *projection); // u_Projection of glsl
  shaderObject->setMat4("u_View", camera->getViewMatrix());

  shaderObject->setVec3("u_LightColor", *lightColor);
  shaderObject->setFloat("u_AmbientStrength", *ambientStrength);
  shaderObject->setVec3("u_LightPos", *lightPos);
  shaderObject->unbind();
}

void Practice::render() {
  shaderObject->bind();
  glEnable(GL_CULL_FACE);
  model->Draw(*shaderObject);
  glDisable(GL_CULL_FACE);
  shaderObject->unbind();
}
