#include "controller.h"

#include "SDL.h"

void Controller::HandleInput(bool &running, std::shared_ptr<TicTacToe> ticTacToe) const{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      if(ticTacToe->getCurrentPlayer() == 1) {
        switch (e.key.keysym.sym) {
          case SDLK_w:
            ticTacToe->moveUp();
            break;

          case SDLK_s:
            ticTacToe->moveDown();
            break;

          case SDLK_a:
            ticTacToe->moveLeft();
            break;

          case SDLK_d:
            ticTacToe->moveRight();
            break;
          case SDLK_t:
            ticTacToe->choosePosition();
            break;
          case SDLK_SPACE:
            ticTacToe->reset();
            break;
        }
      }
      else {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            ticTacToe->moveUp();
            break;

          case SDLK_DOWN:
            ticTacToe->moveDown();
            break;

          case SDLK_LEFT:
            ticTacToe->moveLeft();
            break;

          case SDLK_RIGHT:
            ticTacToe->moveRight();
            break;
          case SDLK_RETURN:
            ticTacToe->choosePosition();
            break;
          case SDLK_SPACE:
            ticTacToe->reset();
            break;
        }
      }
    }
  }
}




