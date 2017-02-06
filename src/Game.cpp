#include <Game.hpp>
#include <iostream>

Game::Game(GameMode mode, AIMode level)
{
	currState = new State();
	currMode = mode;
	automatonState = SELECTION;

	if(mode == SINGLEPLAYER)
		AI_GREEN = new AI(level, (color)GREEN);
	if(mode == WATCH){
		AI_GREEN = new AI(MINMAX, (color)GREEN);
		AI_BLUE = new AI(MCTS, (color)BLUE);
	}
}

Game::~Game()
{
	if(currState)delete currState;
	if(AI_GREEN)delete AI_GREEN;
	if(AI_BLUE)delete AI_BLUE;
}

Status Game::move(std::pair<int,int> cell)
{
	if(currMode == MULTIPLAYER)
		return moveMP(cell);
	else if(currMode == SINGLEPLAYER)
		return moveAI(cell);
	else
		return move_AI_AI(cell);
}

// Move for Multiplayer game
Status Game::moveMP(std::pair<int,int> cell){
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

// Move for Singleplayer game
Status Game::moveAI(std::pair<int,int> cell){
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

		std::pair<int,int> step = AI_GREEN->playOneStep(currState);
		currState->updateState(step);

		if(currState->isGameOver())
			return END;

		automatonState = SELECTION;
		return SUCCESS;
	}
}

// Move for AIvsAI
Status Game::move_AI_AI(std::pair<int,int> cell){
	if(currState->getTurn() == BLUE)
	{
		std::pair<int,int> step = AI_GREEN->playOneStep(currState);
		currState->updateState(step);

		if(currState->isGameOver())
			return END;
		return SUCCESS;
	}
	else
	{
		std::pair<int,int> step = AI_BLUE->playOneStep(currState);
		currState->updateState(step);

		if(currState->isGameOver())
			return END;
		return SUCCESS;
	}
}

// Get the color at a given position corresponding to current game state
color Game::getColoratPosition(std::pair<int,int> pos){
	return currState->getColoratPosition(pos);
}

// Get the automaton state
GameAutomatonState Game::getAutomatonState(){
	return automatonState;
}

// Get the color for the winner
color Game::getWinner(){
	int value = currState->getValue(GREEN);
	if(value > 0)return GREEN;
	else if(value <0)return BLUE;
	else return BLANK;
}

// Get the color of the player with current turn
color Game::getTurn(){
	return currState->getTurn();
}