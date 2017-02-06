#ifndef GAME_HPP
#define GAME_HPP

#include <State.hpp>
#include <AI.hpp>
#include <utility>

class Game{
public:
	Game(GameMode mode, AIMode level);
	~Game();
	Status moveMP(std::pair<int,int> cell);
	Status moveAI(std::pair<int,int> cell);
	Status move_AI_AI(std::pair<int,int> cell);
	color getColoratPosition(std::pair<int,int> pos);
	GameAutomatonState getAutomatonState();
	Status move(std::pair<int,int> cell);
	color getWinner();
	color getTurn();

private:
	State* currState;
	AI *AI_GREEN;
	AI *AI_BLUE;
	std::pair<int,int> currSelection;
	GameMode currMode;
	GameAutomatonState automatonState;
};

#endif