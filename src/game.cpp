#include <game.hpp>

game::game(GameMode mode)
{
	currState->initialize();
	currMode = mode;
	automatonState = WAITING_FOR_PLAYER;
}

void game::playMultiplayerGame(){
	if(automatonState == WAITING_FOR_PLAYER)
	{
		if(currState->turn == PLAYER1)std::cout<<"PLAYER2's turn ! "<<std::endl;
		else std::cout<<"PLAYER1's turn ! "<<std::endl;

		std::pair<int,int> from(0,0);
		std::pair<int,int> to(0,0);

		std::cout<<"From Position: ";
		std::cin>>from.first>>from.second;

		std::cout<<"To Position: ";
		std::cin>>to.first>>to.second;

		if(!currState->validMove(move)){
			std::cout<<"Move Invalid !";
			automatonState = WAITING_FOR_PLAYER;
		}
		else{
			automatonState = UPDATE_STATE;
		}
	}
	else if(automatonState == UPDATE_STATE){
		currState->updateState();
		if(currState->isGameOver())automatonState == END;
		else automatonState == WAITING_FOR_PLAYER;
	}
	else if{automatonState == END}
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