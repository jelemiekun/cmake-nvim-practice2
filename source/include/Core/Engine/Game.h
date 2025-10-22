#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Game {
  // Constructors & Destructors
public:
  Game();
  Game(Game &&) = default;
  Game(const Game &) = default;
  Game &operator=(Game &&) = default;
  Game &operator=(const Game &) = default;
  ~Game();

  // Static Methods
public:
  static Game *getInstance();

  // Class Private Attributes
  SDL_Window *m_Window;
  SDL_GLContext m_GLContext;
  bool m_Running;
  float deltaTime;

  // Class Public Methods
public:
  void run();

  // Class Private Methods
private:
  // Initializers
  void setOpenGLAttributes();
  bool initSDL();
  bool initWindow();
  bool initOpenGLContext();
  bool loadGLAD();

  // Game Loop
  void gameLoop();

  void handleInput();
  void update();
  void render();

  // Others
  void calculateDeltaTime();
};
