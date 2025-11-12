#include "Practice.h"
#include "Camera.h"
#include "Game.h"
#include "ImGUIWindow.h"
#include "Model.h"
#include "Physics.h"
#include "Shader.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <bullet/LinearMath/btTransform.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>
#include <spdlog/spdlog.h>
#include <string>

namespace ProgramValues {
Shader sourceShader;
Camera *camera = nullptr;
Camera cameraFF;
Camera cameraFPV;
Camera cameraFV;
Camera cameraBV;
Model shipInClouds;
glm::mat4 projection;
} // namespace ProgramValues

void Practice::init() {
  // Shaders
  ProgramValues::sourceShader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());

  // Cameras
  ProgramValues::cameraFF =
      Camera(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
  // TODO:
  ProgramValues::camera = &ProgramValues::cameraFF;

  // Models
  ProgramValues::shipInClouds.loadModel(std::string(ASSET_PATH) +
                                        "/models/earth_1.glb");

  // Projection
  Game *p_Game = Game::getInstance();
  ProgramValues::projection = glm::perspective(
      glm::radians(60.0f),
      (float)p_Game->m_WindowWidth / (float)p_Game->m_WindowHeight, 0.1f,
      100.0f);
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  // Cameras
  ProgramValues::camera->processKeyboard(event, window);
  ProgramValues::camera->processMouseMotion(event);
}

void Practice::update(const float &deltaTime) {
  Shader *p_SourceShader = &ProgramValues::sourceShader;
  Camera *p_Camera = ProgramValues::camera;
  Model *p_ShipInClouds = &ProgramValues::shipInClouds;

  // Shaders
  p_SourceShader->setMat4("u_View", p_Camera->getViewMatrix());
  p_SourceShader->setMat4("u_Projection", ProgramValues::projection);

  // Models
  Physics *physics = Physics::getInstance();
  {
  }

  // Cameras
  p_Camera->update();
}

void Practice::render() {
  static ImGUIWindow *imGUIWindow = ImGUIWindow::getInstance();

  glBindFramebuffer(GL_FRAMEBUFFER, imGUIWindow->fbo);
  glViewport(0, 0, imGUIWindow->renderWidth, imGUIWindow->renderHeight);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ProgramValues::sourceShader.bind();
  ProgramValues::shipInClouds.Draw(ProgramValues::sourceShader);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Practice::free() {
  spdlog::info("Deleting gameplay practice resources...");
  ProgramValues::sourceShader.free();
  spdlog::info("Gameplay practice resources destroyed successfully.");
}
