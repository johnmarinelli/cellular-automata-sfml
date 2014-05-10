#include "World.hpp"

namespace CA{

World::World(sf::RenderWindow& target) : mRenderSystem(target)
{
}

void World::init()
{
	for(int i = 0; i < 10; i++){
		Cell cell(i*5, i*5, true);
		mCells.push_back(cell);
		mRenderSystem.addCell(cell);
	}

	std::cout << mCells.size() << std::endl;
	mRenderSystem.temp();
}

void World::update(float dTime)
{
}

void World::render()
{
	mRenderSystem.render();
}

World::~World()
{
}

}
