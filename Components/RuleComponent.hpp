#ifndef RULECOMPONENT_HPP
#define RULECOMPONENT_HPP

#include <vector>
#include <iostream>
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
