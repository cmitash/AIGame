#ifndef AI_HPP
#define AI_HPP

#include <state.hpp>
#include <utility>

class AI_minmax{
	public:
		AI_minmax(AIMode level);
		std::pair<int,int> playOneStep(state* currstate);
		std::pair<int,int> playRandomStep(state* currstate);
		int MaxValue(state* currstate, std::pair<int,int> action, int stDepth);
		int MinValue(state* currstate, std::pair<int,int> action, int stDepth);
		std::pair<int,int> playMinMaxStep(state* currstate);
	private:
		AIMode mode;
};

#endif