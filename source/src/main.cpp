#include "Game.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
  spdlog::info("Hello from main.cpp!");
  Game::greet();
  return 0;
}
