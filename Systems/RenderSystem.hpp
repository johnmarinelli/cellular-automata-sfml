#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "BaseSystem.hpp"

namespace CA{

class RenderSystem : public BaseSystem
{
private:
	sf::RenderWindow* mWindow;
	CellArray mCells;
	
public:
	RenderSystem(sf::RenderWindow& target) : mWindow(&target)
	{	
		mCells.reserve((WINDOW_WIDTH / CA::CELL_WIDTH) * (WINDOW_HEIGHT / CA::CELL_HEIGHT));
	}

	void addCell(std::shared_ptr<CA::Cell> cell)
	{
		mCells.push_back(cell);
	}

	void render()
	{
		for(auto cell : mCells){
			if(cell->getState()){
				auto rect = cell->getRectComponent().getFloatRect();
				auto shape = cell->getShapeComponent();

				shape.getRectangleShape().setFillColor(cell->getGraphics());
				shape.getRectangleShape().setPosition(rect.left, rect.top);
				mWindow->draw(shape.getRectangleShape());	
			}
		}
	}

	~RenderSystem()
	{
		mCells.clear();
	}
};

}

#endif

