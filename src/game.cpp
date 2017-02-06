#include <game.hpp>
#include <iostream>

game::game(GameMode mode, AIMode level)
{
	currState = new state();
	currState->initialize();
	currMode = mode;
	automatonState = SELECTION;

	if(mode == SINGLEPLAYER)
		AI = new AI_minmax(level);
}

Status game::move(std::pair<int,int> cell)
{
	if(currMode == MULTIPLAYER)
		return moveMP(cell);
	else
		return moveAI(cell);
}

Status game::moveMP(std::pair<int,int> cell){
	if(automatonState == SELECTION)
	{
		if(!currState->validateSelection(cell)){
			return BAD_SELECTION;
		}
		else{
			currSelection = cell;
			automatonState = MOVE;
			return SUCCESS;
		}
	}
	else if(automatonState == MOVE)
	{
		currState->clearSelectionOptions(currSelection);
		if(!currState->validMove(currSelection, cell))
		{
			automatonState = SELECTION;
			return INVALID_MOVE;
		}
		currState->updateState(cell);
		if(currState->isGameOver())
		{
			return END;
		}
		else{
			automatonState = SELECTION;
			return SUCCESS;
		}
	}
}

Status game::moveAI(std::pair<int,int> cell){
	if(automatonState == SELECTION)
	{
		if(!currState->validateSelection(cell)){
			return BAD_SELECTION;
		}
		else{
			currSelection = cell;
			automatonState = MOVE;
			return SUCCESS;
		}
	}
	else if(automatonState == MOVE)
	{
		currState->clearSelectionOptions(currSelection);
		if(!currState->validMove(currSelection, cell))
		{
			automatonState = SELECTION;
			return INVALID_MOVE;
		}
		currState->updateState(cell);

		if(currState->isGameOver())
			return END;

		std::pair<int,int> step = AI->playOneStep(currState);
		currState->updateState(step);

		if(currState->isGameOver())
			return END;

		automatonState = SELECTION;
		return SUCCESS;
	}
}

color game::getColoratPosition(std::pair<int,int> pos){
	return currState->getColoratPosition(pos);
}

GameAutomatonState game::getAutomatonState(){
	return automatonState;
}

color game::getWinner(){
	int value = currState->getValue();
	if(value > 0)return GREEN;
	else if(value <0)return BLUE;
	else return BLANK;
}

color game::getTurn(){
	return currState->getTurn();
}