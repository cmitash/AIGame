#include <iostream>
#include <climits>
#include <stdlib.h> 

#include <AI.hpp>

AI::AI(AIMode level, color col){
mode = level;
AIcolor = col;
}

AI::~AI(){
}

std::pair<int,int> AI::playOneStep(State* currstate){
	if(mode == RANDOM)
		return playRandomStep(currstate);
	else if(mode == MINMAX)
		return playMinMaxStep(currstate);
	else if(mode == MCTS)
		return playMCTSStep(currstate);
}

// Run simulation for MCTS
int AI::runSimulation(State* currstate, std::pair<int,int> action)
{
	int winCount = 0;
	for(int i=0;i<NUM_SIMULATIONS;i++){
		int numMoves = 0;
		State *mState = new State(currstate);
		while(!mState->isGameOver() && numMoves < THRES_MOVES){
			std::vector<std::pair<int,int> > actions = mState->getAllActions();
			int selection = rand() % actions.size();
			mState->updateState(actions[selection]);
			numMoves++;
		}
		if(mState->getValue(AIcolor) > 0)winCount++;
	}
	return winCount;
}

// play one step for MCTS
std::pair<int,int> AI::playMCTSStep(State* currstate){
	std::cout<<"MCTS::playOneStep"<<std::endl;
	std::vector<std::pair<int,int> > actions = currstate->getAllActions();
	
	int max_value = INT_MIN;
	int best_action = 0;

	for(int i=0;i<actions.size();i++)
	{
		int utility = runSimulation(currstate, actions[i]);
	}

	return actions[best_action];
}

// Play one step of random AI
std::pair<int,int> AI::playRandomStep(State* currstate){
	std::cout<<"Random::playOneStep"<<std::endl;
	std::vector<std::pair<int,int> > actions = currstate->getAllActions();
	
	int selection = rand() % actions.size();
	return actions[selection];
}

// Play one step for MINMAX AI
std::pair<int,int> AI::playMinMaxStep(State* currstate){
	std::cout<<"MINMAX::playOneStep"<<std::endl;
	int max_value = INT_MIN;
	int best_action = 0;

	std::vector<std::pair<int,int> > actions = currstate->getAllActions();
	for(int i=0;i<actions.size();i++)
	{
		int utility = MinValue(currstate, actions[i], currstate->getDepth());
		if( utility > max_value){
			max_value = utility;
			best_action = i;
		}
	}
	return actions[best_action];
}

// Support function for MINMAX AI
int AI::MinValue(State* currstate, std::pair<int,int> action, int stDepth){

	State *mState = new State(currstate);
	mState->updateState(action);

	if(mState->isGameOver() || (mState->getDepth() - stDepth) > THRES_DEPTH )
		return mState->getValue(AIcolor);

	int min_value = INT_MAX;
	std::vector<std::pair<int,int> > actions = mState->getAllActions(); 

	for(int i=0;i<actions.size();i++)
	{
		int utility = MaxValue(mState, actions[i], stDepth);
		if( utility < min_value)
			min_value = utility;
	}
	return min_value;
}

// Support function for MINMAX AI
int AI::MaxValue(State* currstate, std::pair<int,int> action, int stDepth){

	State *mState = new State(currstate);
	mState->updateState(action);

	if(mState->isGameOver() || (mState->getDepth() - stDepth) > THRES_DEPTH )
		return mState->getValue(AIcolor);


	int max_value = INT_MIN;
	std::vector<std::pair<int,int> > actions = mState->getAllActions(); 

	for(int i=0;i<actions.size();i++)
	{
		int utility = MinValue(mState, actions[i], stDepth);
		if( utility > max_value)
			max_value = utility;
	}
	return max_value;
}
