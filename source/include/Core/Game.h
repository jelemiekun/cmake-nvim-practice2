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
  bool m_Running;

  // Class Public Methods
public:
  void run();

  // Class Private Methods
private:
  void setOpenGLAttributes();
  bool initSDL();
  bool initWindow();
  bool initOpenGLContext();
  bool loadGLAD();
};
