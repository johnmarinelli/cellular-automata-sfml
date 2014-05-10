#ifndef RECTCOMPONENT_HPP
#define RECTCOMPONENT_HPP

#include <SFML/Graphics.hpp>
#include "BaseComponent.hpp"

/*
*  Collision box component
*/
namespace CA{

class RectComponent : public BaseComponent
{
private:
	sf::FloatRect mRect;

public:
	RectComponent(float x, float y, float width, float height) : mRect(x, y, width, height)
	{
	}
	
	sf::FloatRect& getFloatRect()
	{
		return mRect;
	}

	~RectComponent()
	{
	}
};

}
#endif
