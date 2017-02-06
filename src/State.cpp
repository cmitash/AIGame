#include <State.hpp>
#include <iostream>
#include <stdlib.h>

State::State(){
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
			board[i][j] = BLANK;
	board[0][0] = board[GRID_SIZE-1][GRID_SIZE-1] = GREEN;
	board[0][GRID_SIZE-1] = board[GRID_SIZE-1][0] = BLUE;

	playerColor[PLAYER1] = BLUE;
	playerColor[PLAYER2] = GREEN;
	turn = PLAYER1;
	depth = 1;
};

State::~State(){}

State::State(State *copyState){
depth = copyState->depth;
turn = copyState->turn;
playerColor[PLAYER1] = BLUE;
playerColor[PLAYER2] = GREEN;
FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
			board[i][j] = copyState->board[i][j];
};

// Restore the current state after Selection
void State::clearSelectionOptions(std::pair<int,int> cell)
{
	FOREACH(cell.first-2, cell.first+2, i)
		FOREACH(cell.second-2, cell.second+2, j) {
			if(i < 0 || j < 0 || i >= GRID_SIZE || j>= GRID_SIZE || board[i][j] != RED)
					continue;
			board[i][j] = BLANK;
			}
}

// Update State if current color moves to the destination cell
void State::updateState(std::pair<int,int> cell)
{
	FOREACH(cell.first-1, cell.first+1, i)
		FOREACH(cell.second-1, cell.second+1, j) {
			if(i < 0 || j < 0 || i >= GRID_SIZE || j>= GRID_SIZE || board[i][j] == BLANK)
					continue;
			board[i][j] = playerColor[turn];
		}
	board[cell.first][cell.second] = playerColor[turn];
	turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
	depth++;
}

// Check if the move is valid
bool State::validMove(std::pair<int,int> from, std::pair<int,int> to)
{
	if(board[to.first][to.second] != BLANK){
		std::cout<<"You can only go to blank positions !"<<std::endl;
		return false;
	}
	if(abs(to.first-from.first) > 2 || abs(to.second-from.second) > 2){
		std::cout<<"Too far !"<<std::endl;
		return false;
	}
	else return true;
}

// Is it a valid selection ?
bool State::validateSelection(std::pair<int,int> cell)
{
	bool noOption = true;
	if(board[cell.first][cell.second] != playerColor[turn]){
		std::cout<<"This is not your turn !"<<std::endl;
		return false;
	}

	FOREACH(cell.first-2, cell.first+2, i)
			FOREACH(cell.second-2, cell.second+2, j) {
				if(i < 0 || j < 0 || i >= GRID_SIZE || j>= GRID_SIZE || board[i][j] != BLANK)
						continue;
				board[i][j] = RED;
				noOption = false;
			}

	return !noOption;
}

// Check if the player with current turn has no possible move
bool State::isGameOver()
{
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
		{
			if(board[i][j] == BLANK)
			{
				FOREACH(i-2, i+2, ii)
					FOREACH(j-2, j+2, jj)
					{
						if(ii < 0 || jj < 0 || ii >= GRID_SIZE || jj >= GRID_SIZE)
								continue;
						if(board[ii][jj] == playerColor[turn])return false;
					}
			}
		}
	return true;
}

// Get all possible actions for the current state
std::vector<std::pair<int,int> > State::getAllActions(){
	std::vector<std::pair<int,int> > actions;
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
		{
			if(board[i][j] == playerColor[turn])
			{
				FOREACH(i-2, i+2, ii)
					FOREACH(j-2, j+2, jj)
					{
						if(ii < 0 || jj < 0 || ii >= GRID_SIZE || jj >= GRID_SIZE)
								continue;
						if(board[ii][jj] == BLANK)actions.push_back(std::make_pair(ii,jj));
					}
			}
		}
	return actions;
}

// Get the color at specified position
color State::getColoratPosition(std::pair<int,int> pos){
	return board[pos.first][pos.second];
}

// Get the depth of state
int State::getDepth(){
	return depth;
}

// Get the goodness of the state corresponding to a given color
int State::getValue(color AIcol)
{
	int greenCount = 0;
	int blueCount = 0;
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
		{
			if(board[i][j] == GREEN)greenCount++;
			if(board[i][j] == BLUE)blueCount++;
		}

	if(AIcol == GREEN)
		return (greenCount - blueCount);
	else
		return (blueCount - greenCount);
}

// Get the color of the player with current turn
color State::getTurn()
{
	return playerColor[turn];
}