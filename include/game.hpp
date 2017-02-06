#ifndef GAME_HPP
#define GAME_HPP

#include <state.hpp>
#include <AI_minmax.hpp>
#include <utility>

class game{
public:
	game(GameMode mode, AIMode level);
	Status moveMP(std::pair<int,int> cell);
	Status moveAI(std::pair<int,int> cell);
	color getColoratPosition(std::pair<int,int> pos);
	GameAutomatonState getAutomatonState();
	Status move(std::pair<int,int> cell);
	color getWinner();
	color getTurn();

private:
	state* currState;
	AI_minmax *AI;
	std::pair<int,int> currSelection;
	GameMode currMode;
	GameAutomatonState automatonState;
};

#endif