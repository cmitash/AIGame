#include <state.hpp>
#include <iostream>
#include <stdlib.h>

state::state(){
};

state::state(state *copyState){
depth = copyState->depth;
turn = copyState->turn;
playerColor[PLAYER1] = BLUE;
playerColor[PLAYER2] = GREEN;
FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
			board[i][j] = copyState->board[i][j];
};

void state::initialize()
{
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
			board[i][j] = BLANK;
	board[0][0] = board[GRID_SIZE-1][GRID_SIZE-1] = GREEN;
	board[0][GRID_SIZE-1] = board[GRID_SIZE-1][0] = BLUE;

	playerColor[PLAYER1] = BLUE;
	playerColor[PLAYER2] = GREEN;
	turn = PLAYER1;
	depth = 1;
}

void state::clearSelectionOptions(std::pair<int,int> cell)
{
	FOREACH(cell.first-2, cell.first+2, i)
		FOREACH(cell.second-2, cell.second+2, j) {
			if(i < 0 || j < 0 || i >= GRID_SIZE || j>= GRID_SIZE || board[i][j] != RED)
					continue;
			board[i][j] = BLANK;
			}
}

void state::updateState(std::pair<int,int> cell)
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

bool state::validMove(std::pair<int,int> from, std::pair<int,int> to)
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

bool state::validateSelection(std::pair<int,int> cell)
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

bool state::isGameOver()
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

std::vector<std::pair<int,int> > state::getAllActions(){
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

color state::getColoratPosition(std::pair<int,int> pos){
	return board[pos.first][pos.second];
}

int state::getDepth(){
	return depth;
}

int state::getValue()
{
	int greenCount = 0;
	int blueCount = 0;
	FOREACH(0,GRID_SIZE-1,i)
		FOREACH(0,GRID_SIZE-1,j)
		{
			if(board[i][j] == GREEN)greenCount++;
			if(board[i][j] == BLUE)blueCount++;
		}
	return (greenCount - blueCount);
}

color state::getTurn()
{
	return playerColor[turn];
}