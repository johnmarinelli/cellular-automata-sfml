#ifndef RULECOMPONENT_HPP
#define RULECOMPONENT_HPP

#include <vector>
#include <iostream>
#include <algorithm>

#include "BaseComponent.hpp"

namespace CA{

class RuleComponent : public BaseComponent
{
private:
	typedef std::vector<std::vector<CA::State> > Rule;
	Rule mRule;

public:
	RuleComponent(int height)
	{
		mRule.reserve(height);
	}

	void addLine(std::vector<CA::State> ruleLine)
	{
		mRule.push_back(ruleLine);
	}
	
	void clear()
	{
		mRule.clear();
	}
	
	bool compare(const Rule& other)
	{
		bool isEqual = false;
		uint8_t index = 0;

		//check for more than zero because the bottom row will have 0 elements
		for(auto line : mRule){
			if(other.size() > 0 && std::equal(line.begin(), line.begin() + line.size(), other[index].begin())){
				isEqual = true;
			}
			else{
				isEqual = false;
			}

			index++;
		}
	
		return isEqual;
	}

	void display()
	{
		for(auto i : mRule){
			for(int j = 0; j < i.size(); j++){
				if(i[j] == CA::OFF){
					std::cout << "0";
				}
				else if(i[j] == CA::ON){
					std::cout << "1";
				}
			}
			std::cout << "\n";
		}
	}
};

}

#endif
