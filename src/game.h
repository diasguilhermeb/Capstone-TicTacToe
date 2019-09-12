#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "tic_tac_toe.h"

class Game {
 public:
  Game(std::size_t grid_width, 
       std::size_t grid_height);
  void Run(std::shared_ptr<Controller> controller, 
           std::shared_ptr<Renderer> renderer,
           std::size_t target_frame_duration);
  int getScoreP1() const;
  int getScoreP2() const;
  int getDraws() const;

 private:
  void Update();

  std::shared_ptr<TicTacToe> ticTacToe;
  int m_scoreP1{0};
  int m_scoreP2{0};
  int m_draws{0};
  int m_lastGameId{0};
};

#endif