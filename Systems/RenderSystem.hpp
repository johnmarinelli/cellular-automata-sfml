#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "BaseSystem.hpp"

#include <iostream>
namespace CA{

class RenderSystem : public BaseSystem
{
private:
	sf::RenderWindow* mWindow;
	CellArray mCells;
	
public:
	RenderSystem(sf::RenderWindow& target) : mWindow(&target)
	{
	}

	void addCell(Cell& cell)
	{
		mCells.push_back(cell);
	}

	void render()
	{
		for(auto& cell : mCells){
			if(cell.getState()){
				auto rect = cell.getRectComponent().getFloatRect();
				auto shape = cell.getShapeComponent();

				shape.getRectangleShape().setFillColor(sf::Color(100, 250, 50));
				shape.getRectangleShape().setPosition(rect.left, rect.top);
				mWindow->draw(shape.getRectangleShape());	
			}
		}
	}

	void temp()
	{
		std::cout << mCells.size() << "RS" << std::endl;
	}
	
	~RenderSystem()
	{
	}
};

}

#endif

