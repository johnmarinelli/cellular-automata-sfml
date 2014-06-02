#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Utilities.hpp"
#include <SFML/Graphics.hpp>
#include "math.h"

namespace CA{

const float CELL_WIDTH = 10.0;
const float CELL_HEIGHT = 10.0;

const int GRIDCELL_WIDTH = WINDOW_WIDTH / CA::CELL_WIDTH;
const int GRIDCELL_HEIGHT = WINDOW_HEIGHT / CA::CELL_HEIGHT;

inline int getIndex(int x, int y)
{    
	return x + (y * GRIDCELL_WIDTH);
}

inline sf::Vector2i getCartesian(int index)
{
	return sf::Vector2i(index % GRIDCELL_WIDTH, std::floor(index / GRIDCELL_WIDTH));
}

}
#endif
