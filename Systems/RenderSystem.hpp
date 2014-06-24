#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "BaseSystem.hpp"
#include <string>

namespace CA{

class RenderSystem : public BaseSystem
{
private:
	sf::RenderWindow* mWindow;
	CellArray mCells;

    int& mPopulation;
    int& mGeneration;
	
public:
	RenderSystem(sf::RenderWindow& target, int& population, int& generation) : mWindow(&target), mPopulation(population), mGeneration(generation)
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


    sf::Font font;
    sf::Text text;
    if(!font.loadFromFile("../assets/courier.ttf")){
//        std::cout << "Couldn't load font";
    }
    else{
        text.setFont(font);
        text.setString(std::to_string(mGeneration));
        text.setCharacterSize(24);
        text.setColor(sf::Color::White);
        mWindow->draw(text);
    }
    
	}

	~RenderSystem()
	{
		mCells.clear();
	}
};

}

#endif

