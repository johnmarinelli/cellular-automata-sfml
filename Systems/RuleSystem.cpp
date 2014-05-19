#include "RuleSystem.hpp"
#include "../Neighborhoods/Moore.hpp"

namespace CA{

void RuleSystem::addNeighborhood(std::shared_ptr<CA::Cell> center)
{
	if(mNeighborhoodType == BaseNeighborhood::Neighborhoods::MOORE){
		mNeighborhoodArray.push_back(std::make_shared<Moore>(center));
	}
}

void RuleSystem::update(float dTime)
{
}

}
