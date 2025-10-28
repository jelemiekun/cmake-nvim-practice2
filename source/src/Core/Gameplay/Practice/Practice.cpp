#include "Practice.h"
#include "Model.h"
#include "Shader.h"
#include <glm/ext/vector_float3.hpp>
#include <spdlog/spdlog.h>
#include <string>

static float vertices1[] = {
    0.0f,  -0.0f, 0.0f, // 0 bottom right
    -1.0f, 0.0f,  0.0f, // 1 bottom left
    -1.0f, 1.0f,  0.0f, // 2 top left
    0.0f,  1.0f,  0.0f  // 3 top right ✅
};

static unsigned int indices1[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

static Shader shader;

static unsigned int VAO1;
static unsigned int VBO1;
static unsigned int EBO1;

static float vertices2[] = {
    1.0f, -1.0f, 0.0f, // 0 bottom right
    0.0f, -1.0f, 0.0f, // 1 bottom left
    0.0f, 0.0f,  0.0f, // 2 top left
    1.0f, 0.0f,  0.0f  // 3 top right ✅
};

static unsigned int indices2[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

static unsigned int VAO2;
static unsigned int VBO2;
static unsigned int EBO2;

void Practice::init() {
  shader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  shader.bind();

  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO1);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO2);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

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

  glBindVertexArray(VAO1);
  glm::vec3 color1(1.0f, 0.0f, 0.0f);
  shader.setVec3("u_Color", color1);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindVertexArray(VAO2);
  glm::vec3 color2 = glm::vec3(0.0f, 1.0f, 0.0f);
  shader.setVec3("u_Color", color2);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //
  //
  //
}
