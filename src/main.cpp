#include <iostream>

#include <game.hpp>

using namespace std;

int main()
{
	// Launch Screen - choose multi player, single player, spectator

	// If multi player is chosen
	game currGame = new game();
	currGame.start((GameType)MULTIPLAYER);
	// Display winner page - ask to play again

	// If single player is chosen

	// If spectator is chosen

	return 0;
}