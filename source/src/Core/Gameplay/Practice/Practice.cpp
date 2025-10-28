#include "Practice.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include <spdlog/spdlog.h>

static Model model;
static Shader shader;
static Camera camera;

void Practice::init() {
  model.loadModel(std::string(ASSET_PATH) + "models/earth_1.glb");
  shader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  //
  //
  //
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  camera.processKeyboard(event, window);
  camera.processMouseMotion(event);
  //
  //
  //
}

void Practice::update(const float &deltaTime) {
  camera.setViewToShader(shader.ID, "u_View");
  camera.update();
  //
  //
  //
}

void Practice::render() {
  //
  //
  //
}
