#include "Practice.h"
#include "Camera.h"
#include "Shader.h"
#include <spdlog/spdlog.h>

static float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                           0.0f,  0.0f,  0.5f, 0.0f};

static unsigned int VBO;
static unsigned int VAO;

static Shader shader;

void Practice::init() {
  shader.init((std::string(CMAKE_SOURCE_PATH) + "shaders/source.glsl").c_str());
  shader.bind();

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  //
  //
  //
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
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
