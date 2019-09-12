#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "SDL.h"
#include <vector>

class TicTacToe
{
public:
 	TicTacToe(int gridWidth, int gridHeight);	

	/* navigation functions */
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void choosePosition();

	/*change state functions */
	void update();		//basically, update current selected cell
	void reset();		//starts a new game

	/* get functions */
	bool currentPosFree()const;			//return true when current cell was not choosed yet
	bool gameOver()const;				//return true when the game is over
	int getWinner()const;				//return winner (1 = player 1, 2 = player 2, 3 = draw)
	int getGameId()const;				//return game identifier
	int getCurrentPlayer()const;		//return which player is the turn

	/* return graphic elements to be plotted by render */
	std::vector<SDL_Point> getGridBody()const;			//game grid (3x3)
	std::vector<SDL_Point> getMoves()const;				//players moves
	std::vector<SDL_Point> getCurrentSelection()const;	//current cell selected
	std::vector<SDL_Point> getWinnerLine()const;		//line to mark cells that make player win the game

private:

	void checkWinner();							//verify if there is a winner
	int getXReference(int x);					//obtain x axis reference to draw
	int getYReference(int y);					//obtain y axis reference to draw
	void createO(int xRef, int yRef);			//create an "O" symbol
	void createX(int xRef, int yRef);			//create an "X" symbol
	void createSquare(int xRef, int yRef);		//create a square to mark current cell
	void createWinLine();						//create a line to mark current cells that configure win

	bool evalRows();							//evaluate rows to find 3 equal moves of same player
	bool evalCollumns();						//evaluate collumns to find 3 equal moves of same player
	bool evalDiagonal();						//evaluate diagonals to find 3 equal moves of same player

	bool m_gameOver{false};
	int m_winner{0};
	int m_numMoves{0};
	int m_gameId{1};
	int m_currentPlayer{1};
	int m_winPoints[2];
	int m_currentPos{5};
	int m_lastPos{0};
	int m_gridWidth;
	int m_gridHeight;
	int m_symbolWidth;
	int m_symbolHeight;

	int grid[9]={0,0,0,0,0,0,0,0,0};			//the 9 positions represents the game 3x3 grid: [1, 2, 3]
												//												[4, 5, 6]
												//												[7, 8, 9]
	std::vector<SDL_Point> m_gridBody;
	std::vector<SDL_Point> m_moves;
	std::vector<SDL_Point> m_currentSelection;
	std::vector<SDL_Point> m_winnerLine;
};

#endif
