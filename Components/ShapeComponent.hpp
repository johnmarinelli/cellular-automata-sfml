#ifndef SHAPECOMPONENT_HPP
#define SHAPECOMPONENT_HPP

#include "BaseComponent.hpp"

/*
*  Holds the graphical part of the shape; fill color, texture, etc
*/
namespace CA{

class ShapeComponent : public BaseComponent
{
private:
	sf::RectangleShape mShape;

public:
	ShapeComponent(const sf::Vector2f& size, const sf::Texture* texture = nullptr) : mShape(size)
	{
		if(texture) mShape.setTexture(texture);
	}

	sf::RectangleShape& getRectangleShape()
	{
		return mShape;
	}
	
	~ShapeComponent()
	{
	}
};

}

#endif
