#include "renderer.h"
#include <iostream>
#include <string>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Tic-Tac-Toe Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::shared_ptr<TicTacToe> ticTacToe) {

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_Rect block2;
  block2.w = (screen_width / grid_width) ; //0.01*
  block2.h = (screen_height/ grid_height); //0.02*

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render grid
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : ticTacToe->getGridBody()) {
    block.x = point.x*block.w;
    block.y = point.y*block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  // Render moves
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : ticTacToe->getMoves()) {
    block2.x = point.x*block.w;
    block2.y = point.y*block.h;
    SDL_RenderFillRect(sdl_renderer, &block2);
  }
  //Render current position
  if(ticTacToe->currentPosFree()){
    SDL_SetRenderDrawColor(sdl_renderer,124,252,0,1);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer,220,20,60,1);
  }  
  for(SDL_Point const& point : ticTacToe->getCurrentSelection()) {
    block2.x = point.x*block2.w;
    block2.y = point.y*block2.h;
    SDL_RenderFillRect(sdl_renderer, &block2);
  }
  //Render winner line
  SDL_SetRenderDrawColor(sdl_renderer,30,144,255,1);
  for(const SDL_Point& point : ticTacToe->getWinnerLine()) {
    block2.x = point.x*block2.w;
    block2.y = point.y*block2.h;
    SDL_RenderFillRect(sdl_renderer, &block2);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(std::shared_ptr<TicTacToe> ticTacToe, int scoreP1, int scoreP2) {
  std::string title{"Game: "+std::to_string(ticTacToe->getGameId()) +" | Score Player 1: " + std::to_string(scoreP1) + " | Score Player 2: " + std::to_string(scoreP2) + " | Turn: Player "+std::to_string(ticTacToe->getCurrentPlayer())};
  if(ticTacToe->gameOver()) {
    std::string winner {ticTacToe->getWinner() == 3?"  -  It's a draw!":"  -  Player "+std::to_string(ticTacToe->getWinner())+" wins!"};
    title += winner;
  };
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
