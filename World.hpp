#ifndef WORLD_HPP
#define WORLD_HPP

#include "Cell.hpp"
#include "Systems/RenderSystem.hpp"
#include <vector>
#include <memory>

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
