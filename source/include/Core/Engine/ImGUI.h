#pragma once
#include <SDL.h>

class ImGUI {
private:
  ImGUI();

public:
  ImGUI(const ImGUI &) = delete;
  ImGUI &operator=(const ImGUI &) = delete;
  ImGUI(ImGUI &&) = delete;
  ImGUI &operator=(ImGUI &&) = delete;

  static ImGUI *getInstance();

  void init(SDL_Window *window, SDL_GLContext glContext) const;
  void render();
  void clean();
};
