#include <state.hpp>

enum GameMode {
	MULTIPLAYER, SINGLEPLAYER, SPECTATOR
};

enum GameAutomatonState{
	WAITING_FOR_PLAYER, UPDATE_STATE, END
};

class game{
public:
	game(GameMode mode);
	void playMultiplayerGame();
	void playSingleplayerGame();
	void Spectating();

private:
	state* currState;
	GameMode currMode;
	GameAutomatonState automatonState;
};