#include <iostream>
#include <bitset>
#include <algorithm>
#include <iterator>

#include "RuleSystem.hpp"
#include "../Neighborhoods/Moore.hpp"

namespace CA{

//delete this 
int getIndexRuleSystem(int x, int y)
{
    return y + (x * CA::GRIDCELL_HEIGHT);
}

std::vector<CA::State> turnStringToBitset(std::string& bitString)
{
	std::vector<CA::State> bitSet;
	for(auto c : bitString){	
		 if(c == '1'){
			bitSet.push_back(CA::State::ON);
		}
		else{
			bitSet.push_back(CA::State::OFF);
		}
	}
	
	return bitSet;			
}

void RuleSystem::initRules(std::ifstream& rulesFile)
{
	if(!rulesFile){
		std::cerr << "Couldn't open rulesFile" << std::endl;
	}

	else{
		std::string neighborhoodType;
		rulesFile >> neighborhoodType;

		//remember to change mNeighborhoodType 

		while(rulesFile){
			std::string bitString;
			getline(rulesFile, bitString);
	
			//make a bitset from the string.
			//REFACTOR THIS INTO A RULE CLASS
			std::vector<CA::State> bitSet= turnStringToBitset(bitString);				mRules.push_back(bitSet);	
		}	
	}
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
	for(auto hood : mNeighborhoodArray){
		hood->update(dTime);
	}
}

}
