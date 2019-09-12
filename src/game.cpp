#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)    
{  
  ticTacToe = std::make_shared<TicTacToe>(TicTacToe{static_cast<int>(grid_width), static_cast<int>(grid_height)});
}

void Game::Run(std::shared_ptr<Controller> controller, 
               std::shared_ptr<Renderer> renderer,
               std::size_t target_frame_duration) 
  {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller->HandleInput(running, ticTacToe);
    Update();
    renderer->Render(ticTacToe);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer->UpdateWindowTitle(ticTacToe, m_scoreP1, m_scoreP2);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if(ticTacToe->gameOver() && ticTacToe->getGameId() != m_lastGameId) {
    m_lastGameId = ticTacToe->getGameId();
    if (ticTacToe->getWinner() == 1) {
      m_scoreP1++;
      std::cout << "Player 1 wins! \n";
    }
    if (ticTacToe->getWinner() == 2) {
      m_scoreP2++;
      std::cout << "Player 2 wins! \n";
    }
    if (ticTacToe->getWinner() == 3) {
      m_draws++;
      std::cout << "It's a draw! \n";
    }
  }
  ticTacToe->update();
}

int Game::getScoreP1() const {return m_scoreP1;}
int Game::getScoreP2() const {return m_scoreP2;}
int Game::getDraws() const {return m_draws;}