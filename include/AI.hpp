#ifndef AI_HPP
#define AI_HPP

#include <State.hpp>
#include <utility>

class AI{
	public:
		AI(AIMode level, color col);
		~AI();
		std::pair<int,int> playOneStep(State* currstate);
		std::pair<int,int> playRandomStep(State* currstate);
		int MaxValue(State* currstate, std::pair<int,int> action, int stDepth);
		int MinValue(State* currstate, std::pair<int,int> action, int stDepth);
		std::pair<int,int> playMinMaxStep(State* currstate);
		int runSimulation(State* currstate, std::pair<int,int> action);
		std::pair<int,int> playMCTSStep(State* currstate);

	private:
		AIMode mode;
		color AIcolor;
};

#endif