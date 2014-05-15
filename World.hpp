#ifndef WORLD_HPP
#define WORLD_HPP

#include "Cell.hpp"
#include "Systems/RenderSystem.hpp"
#include <vector>
#include <memory>

const int GRIDCELL_WIDTH = WINDOW_WIDTH / CA::CELL_WIDTH;
const int GRIDCELL_HEIGHT = WINDOW_HEIGHT / CA::CELL_HEIGHT;

namespace CA{

class World
{
private:
	typedef std::vector<std::shared_ptr<Cell> > CellArray;

	CA::RenderSystem mRenderSystem;
	CellArray mCells;	

public:
	World(sf::RenderWindow& target);
	void init();
	
	void update(float dTime);
	void render();

	~World();
};

}
#endif
