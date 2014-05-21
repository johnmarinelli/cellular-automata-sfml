#ifndef RULESYSTEM_HPP
#define RULESYSTEM_HPP

#include "BaseSystem.hpp"
#include "../Neighborhoods/BaseNeighborhood.hpp"

namespace CA{

class RuleSystem : public BaseSystem
{
private:
	typedef std::vector<std::shared_ptr<CA::BaseNeighborhood> > NeighborhoodArray;
	NeighborhoodArray mNeighborhoodArray;

	BaseNeighborhood::Neighborhoods mNeighborhoodType;

public:
	RuleSystem(BaseNeighborhood::Neighborhoods hood) : mNeighborhoodType(hood)
	{
	}

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
