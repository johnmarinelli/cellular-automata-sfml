#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Components/RectComponent.hpp"
#include "Components/ShapeComponent.hpp"
#include "Utilities.hpp"

namespace CA{

class Cell
{
private:
	const float CELL_WIDTH = 5;
	const float CELL_HEIGHT = 5;

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
	
	bool getState() const
	{
		return mState;
	}
};

}
#endif
