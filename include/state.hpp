#include <utility>

#define GRID_SIZE 7
#define FOREACH(a,b,i) for(int i=a;i<=b;i++)

enum color{
	BLANK, BLUE, GREEN
};

enum player{
	PLAYER1, PLAYER2
};

class state{
	public:
		state();
		void initialize();
		bool validMove(std::pair<int,int> from, std::pair<int,int> to);
		void updateState(std::pair<int,int> to);
		bool isGameOver();

	private:
		color board[GRID_SIZE][GRID_SIZE];
		player turn;
		color playerColor[2];
};