#define SDL_MAIN_HANDLED
#include "Game.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
  spdlog::info("Initiating program...");

  Game *game = Game::getInstance();
  game->run();

  spdlog::info("Program terminated.");
  return 0;
}
