#include "Practice.h"
#include "Camera.h"
#include "Game.h"
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
Shader screenShader;
Camera *camera = nullptr;
Camera cameraFF;
Camera cameraFPV;
Camera cameraFV;
Camera cameraBV;
Model shipInClouds;
glm::mat4 projection;
unsigned int framebuffer;
unsigned int rbo;
unsigned int quadVAO;
unsigned int textureColorbuffer;
bool windowResized = false;
} // namespace ProgramValues

void Practice::init() {
  // Shaders
  ProgramValues::sourceShader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/source.glsl").c_str());
  ProgramValues::screenShader.init(
      (std::string(CMAKE_SOURCE_PATH) + "/shaders/screen.glsl").c_str());

  ProgramValues::screenShader.bind();
  ProgramValues::screenShader.setInt("u_ScreenTexture", 0);
  ProgramValues::screenShader.unbind();

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

  {
    glGenFramebuffers(1, &ProgramValues::framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, ProgramValues::framebuffer);

    // generate texture
    glGenTextures(1, &ProgramValues::textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, ProgramValues::textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Game::getInstance()->m_WindowWidth,
                 Game::getInstance()->m_WindowHeight, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           ProgramValues::textureColorbuffer, 0);

    // generate renderbuffr object attachments
    glGenRenderbuffers(1, &ProgramValues::rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, ProgramValues::rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                          Game::getInstance()->m_WindowWidth,
                          Game::getInstance()->m_WindowHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // attach it to currently bound framebuffer object
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, ProgramValues::rbo);

    // check
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      spdlog::warn("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  {
    float quadVertices[] = {// positions   // texCoords
                            -1.0f, 1.0f, 0.0f, 1.0f,  -1.0f, -1.0f,
                            0.0f,  0.0f, 1.0f, -1.0f, 1.0f,  0.0f,

                            -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  -1.0f,
                            1.0f,  0.0f, 1.0f, 1.0f,  1.0f,  1.0f};

    GLuint quadVBO;

    glGenVertexArrays(1, &ProgramValues::quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(ProgramValues::quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices,
                 GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
  }
}

void Practice::handleInput(SDL_Event &event, SDL_Window *window) {
  // Cameras
  ProgramValues::camera->processKeyboard(event, window);
  ProgramValues::camera->processMouseMotion(event);
}

void Practice::update(const float &deltaTime) {
  if (ProgramValues::windowResized) {
    ProgramValues::windowResized = false;
    Game *game = Game::getInstance();

    glBindTexture(GL_TEXTURE_2D, ProgramValues::textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, game->m_WindowWidth,
                 game->m_WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, ProgramValues::rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                          game->m_WindowWidth, game->m_WindowHeight);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glViewport(0, 0, game->m_WindowWidth, game->m_WindowHeight);

    ProgramValues::projection = glm::perspective(
        glm::radians(60.0f),
        (float)game->m_WindowWidth / (float)game->m_WindowHeight, 0.1f, 100.0f);
  }

  Shader *p_SourceShader = &ProgramValues::sourceShader;
  Camera *p_Camera = ProgramValues::camera;
  Model *p_ShipInClouds = &ProgramValues::shipInClouds;

  // Shaders
  p_SourceShader->bind();
  p_SourceShader->setMat4("u_View", p_Camera->getViewMatrix());
  p_SourceShader->setMat4("u_Projection", ProgramValues::projection);
  p_SourceShader->unbind();

  // Models
  Physics *physics = Physics::getInstance();
  {
  }

  // Cameras
  p_Camera->update();
}

void Practice::render() {
  glBindFramebuffer(GL_FRAMEBUFFER, ProgramValues::framebuffer);
  glEnable(GL_DEPTH_TEST);

  ProgramValues::sourceShader.bind();
  glClearColor(0.4, 0.4, 0.4, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  ProgramValues::shipInClouds.Draw(ProgramValues::sourceShader);
  ProgramValues::sourceShader.unbind();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDisable(GL_DEPTH_TEST);

  glClearColor(0.4, 0.4, 0.4, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  ProgramValues::screenShader.bind();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, ProgramValues::textureColorbuffer);

  glBindVertexArray(ProgramValues::quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);

  ProgramValues::screenShader.unbind();
}

void Practice::free() {
  spdlog::info("Deleting gameplay practice resources...");
  ProgramValues::sourceShader.free();
  spdlog::info("Gameplay practice resources destroyed successfully.");
}
