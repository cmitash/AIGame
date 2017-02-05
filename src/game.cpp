#include <game.hpp>
#include <iostream>

game::game(GameMode mode)
{
	currState->initialize();
	currMode = mode;
	automatonState = WAITING_FOR_PLAYER;
}

void game::playMultiplayerGame(){
	if(automatonState == WAITING_FOR_PLAYER)
	{
		std::pair<int,int> from(0,0);
		std::pair<int,int> to(0,0);

		std::cout<<"From Position: ";
		std::cin>>from.first>>from.second;

		std::cout<<"To Position: ";
		std::cin>>to.first>>to.second;

		move = make_pair(from, to);
		if(!currState->validMove(from, to)){
			std::cout<<"Move Invalid !";
			automatonState = WAITING_FOR_PLAYER;
		}
		else{
			automatonState = UPDATE_STATE;
		}
	}
	else if(automatonState == UPDATE_STATE){
		currState->updateState(move.second);
		if(currState->isGameOver())automatonState == END;
		else automatonState == WAITING_FOR_PLAYER;
	}
	else if(automatonState == END)
	{
		std::cout<<"GAME OVER !!!"<<std::endl;
	}
}

void game::playSingleplayerGame(){

}

void game::Spectating(){

}

void game::start()
{
	if(currMode == (GameMode)MULTIPLAYER)
		while(automatonState != END)playMultiplayerGame();
	else if(currMode == (GameMode)SINGLEPLAYER)
		playSingleplayerGame();
	else
		Spectating();
}