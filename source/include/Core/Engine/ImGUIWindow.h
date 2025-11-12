#pragma once
#include <SDL.h>

class ImGUIWindow {
private:
  ImGUIWindow();

public:
  ImGUIWindow(const ImGUIWindow &) = delete;
  ImGUIWindow &operator=(const ImGUIWindow &) = delete;
  ImGUIWindow(ImGUIWindow &&) = delete;
  ImGUIWindow &operator=(ImGUIWindow &&) = delete;

  static ImGUIWindow *getInstance();
  static bool willResetLayout;

  bool init(SDL_Window *window, SDL_GLContext glContext) const;
  void createRootDockSpace();
  void resetLayout();
  void render();
  void free();
};
