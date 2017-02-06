#define FOREACH(a,b,i) for(int i=a;i<=b;i++)
#define GRID_SIZE 7
#define CELL_SIZE 80
#define THRES_DEPTH 2

enum GameMode {
	MULTIPLAYER, SINGLEPLAYER
};

enum GameAutomatonState{
	SELECTION, MOVE
};

enum color{
	BLANK, BLUE, GREEN, RED
};

enum player{
	PLAYER1, PLAYER2
};

enum Status{
	SUCCESS,
	BAD_SELECTION,
	INVALID_MOVE,
	END
};

enum AIMode{
	NONE,
	RANDOM,
	MINMAX
};