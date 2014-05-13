#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Components/RectComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Utilities.hpp"

namespace CA{

const float CELL_WIDTH = 20;
const float CELL_HEIGHT = 20;

class Cell
{
private:
	/*
	* I want to do an array of basecomponents but this is such a small project it woul 
	* be a case of overengineering
	*/
	RectComponent mRect;
	ShapeComponent mShape;
	bool mState;

public:
	Cell(float x, float y, bool state) : mRect(x, y, CELL_WIDTH, CELL_HEIGHT), mShape(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT)), mState(state)
	{
	}

	sf::Vector2f getPosition()
	{
		return sf::Vector2f(mRect.getFloatRect().left, mRect.getFloatRect().top);
	}
	
	RectComponent& getRectComponent()
	{
		return mRect;
	}

	ShapeComponent& getShapeComponent()
	{
		return mShape;
	}

	void setState(bool state)
	{
		if(state == false){printf("i am getting set to false\n");};
		mState = state;
	}
	
	bool getState() const
	{
		return mState;
	}
	
	sf::Color getGraphics() const
	{
		return mState ? sf::Color::White : sf::Color::Black;
	}
};

}
#endif
