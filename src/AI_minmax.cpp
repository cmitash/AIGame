#include <iostream>
#include <climits>
#include <stdlib.h> 

#include <AI_minmax.hpp>

AI_minmax::AI_minmax(AIMode level){
mode = level;
}

std::pair<int,int> AI_minmax::playOneStep(state* currstate){
	if(mode == RANDOM)
		return playRandomStep(currstate);
	else if(mode == MINMAX)
		return playMinMaxStep(currstate);
}

std::pair<int,int> AI_minmax::playRandomStep(state* currstate){
	std::cout<<"AI STEP"<<std::endl;
	std::vector<std::pair<int,int> > actions = currstate->getAllActions();
	
	int selection = rand() % actions.size();
	return actions[selection];
}

std::pair<int,int> AI_minmax::playMinMaxStep(state* currstate){
	int max_value = INT_MIN;
	int best_action = 0;

	std::vector<std::pair<int,int> > actions = currstate->getAllActions();
	std::cout<<"AI is thinking !"<<std::endl;
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

int AI_minmax::MinValue(state* currstate, std::pair<int,int> action, int stDepth){

	state *mState = new state(currstate);
	mState->updateState(action);

	if(mState->isGameOver() || (mState->getDepth() - stDepth) > THRES_DEPTH )
		return mState->getValue();

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

int AI_minmax::MaxValue(state* currstate, std::pair<int,int> action, int stDepth){

	state *mState = new state(currstate);
	mState->updateState(action);

	if(mState->isGameOver() || (mState->getDepth() - stDepth) > THRES_DEPTH )
		return mState->getValue();


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
