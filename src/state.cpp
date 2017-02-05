#include <state.hpp>
#include <iostream>
#include <stdlib.h>

state::state(){

};

void state::initialize()
{
	board[0][0] = board[GRID_SIZE-1][GRID_SIZE-1] = GREEN;
	board[0][GRID_SIZE-1] = board[GRID_SIZE-1][0] = BLUE;
	playerColor[PLAYER1] = BLUE;
	playerColor[PLAYER2] = GREEN;
	turn = PLAYER1;
}

void state::updateState(std::pair<int,int> to)
{
	FOREACH(to.first-1, to.first+1, i)
		FOREACH(to.second-1, to.second+1, j)
		{
			if(i < 0 || j < 0 || i >= GRID_SIZE || j>= GRID_SIZE || board[i][j] == BLANK)
					continue;
			board[i][j] = playerColor[turn];
		}
	turn = (turn == PLAYER1) ? PLAYER2 : PLAYER1;
}

bool state::validMove(std::pair<int,int> from, std::pair<int,int> to)
{
	if(board[to.first][to.second] != BLANK){
		std::cout<<"You can only go to blank positions !"<<std::endl;
		return false;
	}
	if(board[from.first][from.second] != playerColor[turn]){
		std::cout<<"This is not your turn !"<<std::endl;
		return false;
	}
	if(abs(to.first-from.first) > 2 || abs(to.second-from.second)){
		std::cout<<"Too far !"<<std::endl;
		return false;
	}
	else return true;
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