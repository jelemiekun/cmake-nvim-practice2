#include "Practice.h"
#include "Model.h"
#include "Shader.h"
#include "Texture2D.h"
#include <cmath>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <spdlog/spdlog.h>
#include <string>

static Shader shader;

static float vertices1[] = {
    0.0f,  -0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 0 bottom right
    -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, // 1 bottom left
    -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, // 2 top left
    0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f  // 3 top right ✅
};

static unsigned int indices1[] = {
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

static unsigned int VAO1;
static unsigned int VBO1;
static unsigned int EBO1;

static Shader shader1;

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

static glm::vec3 color(0.0f);
static glm::mat4 rect1Transform(1.0f);

static float verticesTex[] = {
    // position         // color				// texture
    // coords
    -0.5f, 0.5f,  0.0f, 0.98f,  0.706f, 0.933f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 0.831f, 0.831f, 0.831f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.0f, 1.0f,   0.373f, 0.894f, 1.0f, 1.0f,
    0.5f,  -0.5f, 0.0f, 0.98f,  0.71f,  0.76f,  1.0f, 0.0f};

static unsigned int indicesTex[] = {
    0, 1, 2, 1, 2, 3,
};
static unsigned int VAO3;
static unsigned int VBO3;
static unsigned int EBO3;
static Shader shaderTex;
static Texture2D texture2D1;

void Practice::init() {
  { // Shader init
    shader.init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
    shader1.init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/source2.glsl").c_str());
    shaderTex.init(
        (std::string(CMAKE_SOURCE_PATH) + "/shaders/texture.glsl").c_str());
  }

  { // Rectangle 1 Init
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1,
                 GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
  }

  { // Rectangle 2 Init
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2,
                 GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
  }

  { // Textures Init
    texture2D1.init(std::string(ASSET_PATH) + "/images/images.png");

    glGenVertexArrays(1, &VAO3);
    glBindVertexArray(VAO3);

    glGenBuffers(1, &VBO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTex), verticesTex,
                 GL_STATIC_DRAW);

    glGenBuffers(1, &EBO3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesTex), indicesTex,
                 GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
  }
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  //
  //
  //
}

void Practice::update(const float &deltaTime) {
  { // shader

    shader.bind();
    shader.setMat4("u_Transform", rect1Transform);
    shader.unbind();
  }

  { // shader1
    static int r = 0;
    static int g = 2;
    static int b = 10;
    float rV = sin(r++);
    float gV = sin(g++);
    float bV = sin(b++);

    color = glm::vec3(rV, gV, bV);

    shader1.bind();
    shader1.setVec3("u_Color", color);
    shader1.unbind();
  }
}

void Practice::render() {
  shader.bind();
  glBindVertexArray(VAO1);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  shader.unbind();

  shader1.bind();
  glBindVertexArray(VAO2);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  shader1.unbind();

  shaderTex.bind();
  texture2D1.bind();
  shaderTex.setInt("texture1", 0);
  glBindVertexArray(VAO3);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  shaderTex.unbind();
}
