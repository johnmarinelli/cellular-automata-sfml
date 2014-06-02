#include <iostream>
#include <bitset>
#include <algorithm>
#include <iterator>
#include <assert.h>

#include "RuleSystem.hpp"
#include "../Neighborhoods/Moore.hpp"
#include "../Neighborhoods/OneDimThreeCell.hpp"
#include "../Config.hpp"

namespace CA{

void anchor(){}

std::vector<CA::State> turnStringToBitset(std::string& bitString)
{
	std::vector<CA::State> bitSet;
	for(auto c : bitString){	
		 if(c == '1'){
			bitSet.push_back(CA::State::ON);
		}
		else if(c == '0'){
			bitSet.push_back(CA::State::OFF);
		}
	}
	
	return bitSet;			
}

void RuleSystem::parseTotalisticRules(std::string str, bool isCellAliveRule)
{
	std::size_t gtIndex = str.find(">");
	std::size_t ltIndex = str.find("<");
	std::size_t eqIndex = str.find("==");
	std::size_t assgnIndex = str.find(":");

	if(gtIndex != std::string::npos){
		int condition = str[gtIndex+1] - '0';
		assert(condition >= 0 && condition <= 9);
		isCellAliveRule ? mAliveToDeadGreaterThan.push_back(condition) : mDeadToAliveGreaterThan.push_back(condition);
	}
	else if(ltIndex != std::string::npos){
		int condition = str[ltIndex+1] - '0';
		assert(condition >= 0 && condition <= 9);
		isCellAliveRule ? mAliveToDeadLessThan.push_back(condition) : mDeadToAliveLessThan.push_back(condition);
	}
	else if(eqIndex != std::string::npos){
		int condition = str[eqIndex+2] - '0';
		assert(condition >= 0 && condition <= 9);
		isCellAliveRule ? mAliveToDeadEqualsTo.push_back(condition) : mDeadToAliveEqualsTo.push_back(condition);
	}
}

void RuleSystem::initRules(std::ifstream& rulesFile)
{
	if(!rulesFile){
		std::cerr << "Couldn't open rulesFile" << std::endl;
	}

	else{
		std::string neighborhoodType;
		rulesFile >> neighborhoodType;
		RuleComponent rule(1); //need to make ctor arg a variable for genericism

		while(!rulesFile.eof()){
			std::string str;
			std::getline(rulesFile, str);
			std::cout << str << std::endl;
	
			//specific rules	
			if(str == "/rule"){
				mRules.push_back(rule);
				rule.clear();
			}
			
			//if string starts with 0 or 1, it's a rule line
			else if(str[0] == '1' || str[0] == '0'){	
				//make a bitset from the string.
				std::vector<CA::State> bitSet= turnStringToBitset(str);
				rule.addLine(bitSet);
			}

			//generic, outer totalistic rules
			else if(str == "CELLALIVE"){
				std::getline(rulesFile, str);
				while(str != "/CELLALIVE"){
					parseTotalisticRules(str, true);
					std::getline(rulesFile, str);
				}
			}
			
			else if(str == "CELLDEAD"){
				std::getline(rulesFile, str);
				while(str != "/CELLDEAD"){
					parseTotalisticRules(str, false);
					std::getline(rulesFile, str);
				}
			}
			
			else if(str != ""){
				std::cout << "Couldn't understand " << str << std::endl;
			}
		}
	}
}

void RuleSystem::addNeighborhood(std::shared_ptr<CA::Cell> center)
{
	if(mNeighborhoodType == BaseNeighborhood::Neighborhoods::MOORE){
		auto neighborhood = std::make_shared<Moore>(center);
		mNeighborhoodArray.push_back(neighborhood);
	}

	else if(mNeighborhoodType == BaseNeighborhood::Neighborhoods::ONE_DIM_THREE_CELL){
		auto neighborhood = std::make_shared<OneDimThreeCell>(center);
		mNeighborhoodArray.push_back(neighborhood);
	}
}

void RuleSystem::initNeighborhoods(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
{
	mNeighborhoodArray[getIndex(arrayIndex_x, arrayIndex_y)]->init(cells, arrayIndex_x, arrayIndex_y);	
}

void RuleSystem::update(float dTime)
{
	int index = 0;
	for(auto hood : mNeighborhoodArray){
		CA::BaseNeighborhood::NeighborBitset neighbors = hood->update(dTime);
		int aliveNeighbors = 0;
		int deadNeighbors = 0;

		for(auto line : neighbors){
			for(auto cell : line){
				if(cell == CA::State::ON){
					aliveNeighbors++;
				}
				else if(cell == CA::State::OFF){
					deadNeighbors++;
				}
			}
		}

		/*TOTALISTIC RULES*/	
		if(hood->mCenter->getState()){
			for(auto rule : mAliveToDeadGreaterThan){
				if(aliveNeighbors > rule){
					hood->mCenter->setState(false);
				}
			}

			for(auto rule : mAliveToDeadLessThan){
				if(aliveNeighbors < rule){
					hood->mCenter->setState(false);
				}
			}
		
			for(auto rule : mAliveToDeadEqualsTo){
				if(aliveNeighbors == rule){
					hood->mCenter->setState(false);
				}
			}
		}

		else if(!hood->mCenter->getState()){
			for(auto rule : mDeadToAliveGreaterThan){
				if(aliveNeighbors > rule){
					hood->mCenter->setState(true);
				}
			}

			for(auto rule : mDeadToAliveLessThan){
				if(aliveNeighbors < rule){
					hood->mCenter->setState(true);
				}
			}

			for(auto rule : mDeadToAliveEqualsTo){
				if(aliveNeighbors == rule){
					hood->mCenter->setState(true);
				}
			}
		}

		/*SPECIFIC RULES*/
		for(auto rule : mRules){	
			if(rule.compare(neighbors)){
				anchor();
				rule.compare(neighbors);
				auto coords = getCartesian(index);
				if(coords.y < GRIDCELL_HEIGHT){
					mNeighborhoodArray[getIndex(coords.x, coords.y+1)]->mCenter->setState(true);
				}
			}
		}

		index++;
	}
}

}
