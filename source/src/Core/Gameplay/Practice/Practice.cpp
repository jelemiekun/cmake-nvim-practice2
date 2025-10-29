#include "Practice.h"
#include "Camera.h"
#include "Game.h"
#include "Model.h"
#include "Shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/trigonometric.hpp>
#include <spdlog/spdlog.h>
#include <string>

static Shader shaderObject;
static Camera camera;
static Model model;
static glm::mat4 projection;

void Practice::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  shaderObject.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  model.loadModel(std::string(ASSET_PATH) + "/models/earth_1.glb");

  Game *game = Game::getInstance();
  projection =
      glm::perspective(glm::radians(60.0f),
                       (float)game->m_WindowWidth / (float)game->m_WindowHeight,
                       0.001f, 1000.0f);
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  camera.processKeyboard(event, window);
  camera.processMouseMotion(event);
  //
  //
  //
}

void Practice::update(const float &deltaTime) {
  camera.update();

  shaderObject.bind();
  model.update(shaderObject);                       // u_Model of glsl
  shaderObject.setMat4("u_Projection", projection); // u_Projection of glsl
  shaderObject.setMat4("u_View", camera.getViewMatrix());
  shaderObject.unbind();
  //
  //
  //
}

void Practice::render() {
  shaderObject.bind();
  model.Draw(shaderObject);
  shaderObject.unbind();
  //
  //
}
