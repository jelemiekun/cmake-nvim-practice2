#include "Practice.h"
#include "Shader.h"
#include <spdlog/spdlog.h>
#include <string>

static float vertices[] = {
    0.5f,  -0.5f, 0.0f, // 0 bottom right
    -0.5f, -0.5f, 0.0f, // 1 bottom left
    -0.5f, 0.5f,  0.0f, // 2 top left
    0.5f,  0.5f,  0.0f  // 3 top right ✅
};

static unsigned int indices[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

static Shader shader;

static unsigned int VBO;
static unsigned int VAO;
static unsigned int EBO;

void Practice::init() {
  shader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  shader.bind();

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  shader.unbind();
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
  shader.bind();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //
  //
  //
}
