#ifndef STATE_HPP
#define STATE_HPP

#include <utility>
#include <vector>
#include <tools.hpp>

class State{
	public:
		State();
		State(State* newState);
		~State();
		bool validMove(std::pair<int,int> from, std::pair<int,int> to);
		bool validateSelection(std::pair<int,int> cell);
		void updateState(std::pair<int,int> cell);
		bool isGameOver();
	    color getColoratPosition(std::pair<int,int> pos);
	    void  clearSelectionOptions(std::pair<int,int> cell);
	    std::vector<std::pair<int,int> > getAllActions();
	    int getDepth();
	    int getValue(color AIcolor);
		color getTurn();

	private:
		color board[GRID_SIZE][GRID_SIZE];
		player turn;
		color playerColor[2];
		int depth;
};
#endif