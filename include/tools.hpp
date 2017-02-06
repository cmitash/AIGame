#define FOREACH(a,b,i) for(int i=a;i<=b;i++)

// Size of the playing board
#define GRID_SIZE 7

// Display size in pixels for each cell
#define CELL_SIZE 80

// Depth for MINMAX Algoruthm
#define THRES_DEPTH 2

// Number and depth of simulations for Monte Carlo Tree Search
#define NUM_SIMULATIONS 100
#define THRES_MOVES 50

enum GameMode {
	MULTIPLAYER, SINGLEPLAYER, WATCH
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
	SUCCESS, BAD_SELECTION, INVALID_MOVE, END
};

enum AIMode{
	NONE, RANDOM, MINMAX, MCTS
};