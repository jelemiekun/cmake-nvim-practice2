#include "Game.h"
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

// Constructors and Destructors
Game::Game() {
  spdlog::info("[Game::Game]: An instance of Game class has created.");
}

Game::~Game() {
  spdlog::info("[Game::~Game]: An instance of Game class has been destroyed.");
}

// Static Methods
Game *Game::getInstance() {
  static Game instance;
  return &instance;
}

// Class Public Methods
void Game::run() {
  spdlog::info("Initiating game...");

  m_Running = initSDL() && initWindow() && initOpenGLContext();
}

// Class Private Methods
void Game::setOpenGLAttributes() {
  spdlog::info("Setting OpenGL Attributes...");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  spdlog::info("OpenGL Attributes Setting Done.");
}

bool Game::initSDL() {
  spdlog::info("Initializing SDL...");
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    spdlog::error("SDL Failed to initialize: {}", SDL_GetError());
    return false;
  } else {
    spdlog::info("SDL Initialized successfully.");
    return true;
  }
}

bool Game::initWindow() {
  m_Window =
      SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

  if (!m_Window) {
    spdlog::error("Window creation failed: {}", SDL_GetError());
    return false;
  } else {
    spdlog::info("Window created successfully.");
    return true;
  }
}

bool Game::loadGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    spdlog::error("Failed to initialize GLAD.");
    return false;
  }
  return true;
}
