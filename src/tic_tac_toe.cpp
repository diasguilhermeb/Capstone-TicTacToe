
#include "tic_tac_toe.h"
#include "iostream"

TicTacToe::TicTacToe(int gridWidth, int gridHeight):
	m_gridWidth(gridWidth),
	m_gridHeight(gridHeight)
{
	int row1 = (m_gridHeight-2)/3;
	int row2 = 2*row1 + 1;
	int col1 = (m_gridWidth-2)/3;
	int col2 = 2*col1 + 1;

	/*creating horizontal lines */
	for(auto i=0;i<m_gridWidth;++i) {
		m_gridBody.push_back(SDL_Point{row1,i});
		m_gridBody.push_back(SDL_Point{row2,i});
	}
	/*creating vertical lines */
	for(auto i=0;i<m_gridHeight;++i) {
		m_gridBody.push_back(SDL_Point{i,col1});
		m_gridBody.push_back(SDL_Point{i,col2});
	}
	/*get symbol size*/
	m_symbolWidth = (m_gridWidth-2)/3;
	m_symbolHeight = (m_gridHeight-2)/3;
}

void TicTacToe::moveUp()
{
	if(m_currentPos < 4) {
		m_currentPos += 6;
	}
	else
	{
		m_currentPos -=3;
	}	
}
void TicTacToe::moveDown()
{
	if(m_currentPos > 6){
		m_currentPos -= 6;
	}
	else {
		m_currentPos += 3;
	}
}
void TicTacToe::moveLeft()
{
	if(m_currentPos == 1 || m_currentPos == 4 || m_currentPos == 7) {
		m_currentPos +=2;
	}
	else {
		m_currentPos -= 1;
	}
}
void TicTacToe::moveRight()
{
	if(m_currentPos == 3 || m_currentPos == 6 || m_currentPos == 9) {
		m_currentPos -=2;
	}
	else {
		m_currentPos += 1;
	}
}
void TicTacToe::choosePosition()
{
	if(grid[m_currentPos-1] == 0 && !m_gameOver) {
		grid[m_currentPos-1] = m_currentPlayer;
		m_numMoves++;
		int xRef = getXReference(m_currentPos);
		int yRef = getYReference(m_currentPos);
		if(m_currentPlayer == 1) {
			createO(xRef,yRef);
			checkWinner();
			m_currentPlayer = 2;
		}
		else {
			createX(xRef,yRef);
			checkWinner();
			m_currentPlayer = 1;
		}
	}
}
void TicTacToe::update()
{
	if(m_currentPos != m_lastPos){
		m_lastPos = m_currentPos;
		int xRef = getXReference(m_currentPos);
		int yRef = getYReference(m_currentPos);
		m_currentSelection.clear();
		createSquare(xRef,yRef);
	}
}

void TicTacToe::reset()
{
	memset(grid,0,9*(sizeof(int)));
	m_moves.clear();
	m_winnerLine.clear();
	m_currentPos = 5;
	m_lastPos = 0;
	m_winner = 0;
	m_numMoves = 0;
	m_gameOver = false;
	m_gameId++;
}

bool TicTacToe::currentPosFree()const
{
	return(grid[m_currentPos-1] == 0);
}

int TicTacToe::getWinner()const
{
	return m_winner;
}
int TicTacToe::getGameId()const
{
	return m_gameId;
}
bool TicTacToe::gameOver()const
{
	return m_gameOver;		
}
int TicTacToe::getCurrentPlayer()const
{
	return m_currentPlayer;
}
std::vector<SDL_Point> TicTacToe::getGridBody()const
{
	return m_gridBody;
}
std::vector<SDL_Point> TicTacToe::getMoves()const
{
	return m_moves;
}
std::vector<SDL_Point> TicTacToe::getCurrentSelection()const
{
	return m_currentSelection;
}
std::vector<SDL_Point> TicTacToe::getWinnerLine()const
{
	return m_winnerLine;
}

int TicTacToe::getXReference(int pos)
{
	int xRef = 0;
	if(pos == 2 || pos == 5 || pos == 8) {
		xRef =  1+(m_gridWidth-2)/3;
	}
	if(pos == 3 || pos == 6 || pos == 9) {
		xRef = 2 + 2*(m_gridWidth-2)/3;
	}
	return xRef;
}

int TicTacToe::getYReference(int pos)
{
	int yRef = 0;	
	if(pos > 3) {
		yRef =  1+(m_gridHeight-2)/3;
	}
	if(pos > 6){
		yRef = 2 + 2*(m_gridHeight-2)/3;
	}
	return yRef;
}

void TicTacToe::createO(int xRef, int yRef)
{
	int x1, x2, y1, y2;	
	/*first horizontal dot of 'O' */
	m_moves.push_back(SDL_Point{xRef, m_symbolHeight/2 + yRef});
	/*last horizontal dot of 'O' */
	m_moves.push_back(SDL_Point{m_symbolWidth - 1 + xRef, m_symbolHeight/2 + yRef});
	/*middle dot of 'O' - superior*/
	m_moves.push_back(SDL_Point{m_symbolWidth/2 + xRef, yRef});
	/*middle dot of 'O' - inferior */
	m_moves.push_back(SDL_Point{m_symbolWidth/2 + xRef, m_symbolHeight - 1 + yRef});
	/*other dots */
	for(int i=1; i<(m_symbolHeight - 3)/2 + 1; ++i) {
		x1 = xRef + i;		
		x2 = xRef + m_symbolWidth-1 - i;
		y1 =  m_symbolHeight/2 + yRef - i;
		y2 = m_symbolHeight/2 + yRef + i;
		m_moves.push_back(SDL_Point{x1,y1});
		m_moves.push_back(SDL_Point{x1,y2});
		m_moves.push_back(SDL_Point{x2,y1});
		m_moves.push_back(SDL_Point{x2,y2});
	}	
}

void TicTacToe::createX(int xRef, int yRef)
{
	int x,y1,y2;
	for(int i=0;i<m_symbolHeight;++i) {
		x = xRef + i;
		y1 = yRef + i;
		y2 = yRef + m_symbolHeight - 1 - i;
		/*create first diagonal of X */
		m_moves.push_back(SDL_Point{x,y1});
		/*create second diagonal of X */
		m_moves.push_back(SDL_Point{x,y2});
	}
}

void TicTacToe::createSquare(int xRef, int yRef)
{
	int x1,x2,y1,y2;
	y1 = yRef;
	y2 = yRef + m_symbolHeight -1;
	for(int i=0;i<m_symbolWidth;++i) {
		x1 = xRef + i;		
		m_currentSelection.push_back(SDL_Point{x1,y1});
		m_currentSelection.push_back(SDL_Point{x1,y2});			
	}
	x1 = xRef;
	x2 = xRef + m_symbolWidth -1;
	for(int i=0;i<m_symbolHeight;++i) {
		y1 = yRef + i;
		m_currentSelection.push_back(SDL_Point{x1,y1});
		m_currentSelection.push_back(SDL_Point{x2,y1});	
	}
	
}

void TicTacToe::createWinLine()
{
	int xRef1 = getXReference(m_winPoints[0]);
	int yRef1 = getYReference(m_winPoints[0]);
	int xRef2 = getXReference(m_winPoints[1]);
	int yRef2 = getYReference(m_winPoints[1]);
	int numItems;	
	if(xRef1 == xRef2) {
		numItems = 2+2*m_symbolHeight;
		for(int i=0;i<numItems;++i){
			m_winnerLine.push_back(SDL_Point{xRef1+m_symbolWidth/2,i+m_symbolHeight/2});
		}
	}
	else if(yRef1 == yRef2) {
		numItems = 2+2*m_symbolWidth;
		for(int i=0;i<numItems;++i){
			m_winnerLine.push_back(SDL_Point{i+m_symbolWidth/2,yRef1+m_symbolHeight/2});
		}
	}
	else{
		numItems = (m_symbolWidth+m_symbolHeight);
		if(xRef1 > 0){
			for(int i=0;i<numItems;++i){
				m_winnerLine.push_back(SDL_Point{xRef1-i+m_symbolWidth/2,i+m_symbolHeight/2});	
			}
		}
		else {
			for(int i=0;i<numItems;++i){		
				m_winnerLine.push_back(SDL_Point{i+m_symbolWidth/2,i+m_symbolHeight/2});
			}
		}
	}	
}

void TicTacToe::checkWinner(){
	if(evalRows() || evalCollumns() || evalDiagonal()) {
		m_gameOver = true;
		m_winner = m_currentPlayer;	
		createWinLine();
	}
	else if(m_numMoves == 9){
		m_gameOver = true;
		m_winner = 3; //draw
	}	
}

bool TicTacToe::evalRows()
{
	if(grid[0] == grid[1] && grid[0] == grid[2] && grid[0] != 0) {
		m_winPoints[0] = 1; m_winPoints[1] = 3;
		return true;
	}
	if(grid[3] == grid[4] && grid[3] == grid[5] && grid[3] != 0) {
		m_winPoints[0] = 4; m_winPoints[1] = 6;
		return true;
	}
	if(grid[6] == grid[7] && grid[6] == grid[8] && grid[6] != 0) {
		m_winPoints[0] = 7; m_winPoints[1] = 9;
		return true;
	}
	return false;
}

bool TicTacToe::evalCollumns()
{
	if(grid[0] == grid[3] && grid[0] == grid[6] && grid[0] != 0) {
		m_winPoints[0] = 1; m_winPoints[1] = 7;
		return true;
	}
	if(grid[1] == grid[4] && grid[1] == grid[7] && grid[1] != 0) {
		m_winPoints[0] = 2; m_winPoints[1] = 8;
		return true;
	}
	if(grid[2] == grid[5] && grid[2] == grid[8] && grid[2] != 0) {
		m_winPoints[0] = 3; m_winPoints[1] = 9;
		return true;
	}
	return false;
}

bool TicTacToe::evalDiagonal()
{
	if(grid[0] == grid[4] && grid[0] == grid[8] && grid[0] != 0) {
		m_winPoints[0] = 1; m_winPoints[1] = 9;
		return true;
	}
	if(grid[2] == grid[4] && grid[2] == grid[6] && grid[2] != 0) {
		m_winPoints[0] = 3; m_winPoints[1] = 7;
		return true;
	}
	return false;
}