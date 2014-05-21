#include "RuleSystem.hpp"
#include "../Neighborhoods/Moore.hpp"

namespace CA{

//delete this 
int getIndexRuleSystem(int x, int y)
{
    return y + (x * CA::GRIDCELL_HEIGHT);
}

void RuleSystem::addNeighborhood(std::shared_ptr<CA::Cell> center)
{
	if(mNeighborhoodType == BaseNeighborhood::Neighborhoods::MOORE){
		auto neighborhood = std::make_shared<Moore>(center);
		mNeighborhoodArray.push_back(neighborhood);
	}
}

void RuleSystem::initNeighborhoods(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
{
	mNeighborhoodArray[getIndexRuleSystem(arrayIndex_x, arrayIndex_y)]->init(cells, arrayIndex_x, arrayIndex_y);	
}

void RuleSystem::update(float dTime)
{
}

}
