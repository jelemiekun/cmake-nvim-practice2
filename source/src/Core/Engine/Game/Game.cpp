#include "Game.h"
#include "Practice.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_video.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

// Constructors and Destructors
Game::Game() : m_Window(nullptr) {
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

  setOpenGLAttributes();

  m_Running = initSDL() && initWindow() && initOpenGLContext() && loadGLAD();

  if (m_Running) {
    spdlog::info("Initializing practice...");
    Practice::init();

    spdlog::info("Entering game loop...");

    gameLoop();
  } else {
    spdlog::error("Initialization failed. Failed to enter game loop.");
  }
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
  m_Window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 800, 600,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (!m_Window) {
    spdlog::error("Window creation failed: {}", SDL_GetError());
    return false;
  } else {
    spdlog::info("Window created successfully.");
    return true;
  }
}

bool Game::initOpenGLContext() {
  m_GLContext = SDL_GL_CreateContext(m_Window);
  if (!m_GLContext) {
    spdlog::error("SDL_GL_CreateContext failed: {}", SDL_GetError());
    return false;
  }

  SDL_GL_SetSwapInterval(
      0); // Disable VSync: allows rendering at uncapped FPS instead of syncing
          // to monitor's refresh rate (e.g., 60Hz)
  spdlog::info("SDL Context created successfully.");
  return true;
}

bool Game::loadGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    spdlog::error("Failed to initialize GLAD.");
    return false;
  }
  spdlog::info("GLAD loaded successfully.");
  return true;
}

void Game::gameLoop() {
  while (m_Running) {
    handleInput();
    update();
    render();
  }
  spdlog::info("Gameloop terminated.");
}

void Game::handleInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT)
      m_Running = false;

    Practice::handleInput(event);
  }
}

void Game::update() {
  calculateDeltaTime();
  Practice::update(deltaTime);
}

void Game::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Practice::render();

  SDL_GL_SwapWindow(m_Window);
}

void Game::calculateDeltaTime() {
  static Uint64 lastCounter = SDL_GetPerformanceCounter();
  Uint64 currentCounter = SDL_GetPerformanceCounter();

  deltaTime = static_cast<float>(currentCounter - lastCounter) /
              static_cast<float>(SDL_GetPerformanceFrequency());

  lastCounter = currentCounter;
}

// TODO: init imgui
// TODO: imgui source file
// TODO: build imgui repo
