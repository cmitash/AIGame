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

	private:
		color board[GRID_SIZE][GRID_SIZE] = {BLANK};
		player turn;
		color playerColor[2] = {BLANK};
};