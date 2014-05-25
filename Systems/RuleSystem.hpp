#ifndef RULESYSTEM_HPP
#define RULESYSTEM_HPP

#include <fstream>
#include "BaseSystem.hpp"
#include "../Neighborhoods/BaseNeighborhood.hpp"
#include "../Components/RuleComponent.hpp"

namespace CA{

class RuleSystem : public BaseSystem
{
private:
	typedef std::vector<std::shared_ptr<CA::BaseNeighborhood> > NeighborhoodArray;
	typedef std::vector<RuleComponent> RuleArray;
	typedef std::vector<int> IntArray;

	NeighborhoodArray mNeighborhoodArray;
	RuleArray mRules;

	IntArray mAliveToDeadGreaterThan;
	IntArray mDeadToAliveGreaterThan;
	IntArray mAliveToDeadLessThan;
	IntArray mDeadToAliveLessThan;
	IntArray mAliveToDeadEqualsTo;
	IntArray mDeadToAliveEqualsTo;

	BaseNeighborhood::Neighborhoods mNeighborhoodType;

	void parseTotalisticRules(std::string, bool);

public:
	RuleSystem(BaseNeighborhood::Neighborhoods hood) : mNeighborhoodType(hood)
	{
	}

	void initRules(std::ifstream& rulesFile);
	void addNeighborhood(std::shared_ptr<CA::Cell> center);
	void initNeighborhoods(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y);

	void update(float dTime);

	~RuleSystem()
	{
		mNeighborhoodArray.clear();
	}
};

}

#endif
