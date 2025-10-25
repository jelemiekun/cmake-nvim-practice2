#include "Practice.h"
#include "Model.h"
#include <spdlog/spdlog.h>

static Model model;

void Practice::init() {
  model.loadModel(std::string(ASSET_PATH) + "models/earth_1.glb");
  //
  //
  //
}

void Practice::handleInput(SDL_Event &event) {
  //
  //
  //
}

void Practice::update(const float &deltaTime) {
  //
  //
  //
}

void Practice::render() {
  //
  //
  //
}
