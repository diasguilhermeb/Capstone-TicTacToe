#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include "tic_tac_toe.h"

class Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<TicTacToe> ticTacToe) const;

   
};

#endif