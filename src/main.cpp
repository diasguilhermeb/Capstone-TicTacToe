#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{80};
  constexpr std::size_t kGridHeight{80};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(std::make_shared<Controller>(controller), std::make_shared<Renderer>(renderer), kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score P1: " << game.getScoreP1() << "\n";
  std::cout << "Score P2: " << game.getScoreP2() << "\n";
  std::cout << "Draws: " << game.getDraws() << "\n";
 
  return 0;
}