#include "World.hpp"

namespace CA{

World::World(sf::RenderWindow& target) : mRenderSystem(target)
{
	mCells.reserve((WINDOW_WIDTH / CA::CELL_WIDTH) * (WINDOW_HEIGHT / CA::CELL_HEIGHT));
}

void World::init()
{
	for(int i = 0; i < WINDOW_WIDTH; i+=CA::CELL_WIDTH){
		for(int j = 0; j < WINDOW_HEIGHT; j+=CA::CELL_HEIGHT){
			Cell cell(i, j, false);
			mCells.push_back(cell);
			mRenderSystem.addCell(cell);
		}
	}	
}

void World::update(float dTime)
{
	for(int i = 0; i < WINDOW_WIDTH / CELL_WIDTH; ++i){
		for(int j = 0; j < WINDOW_HEIGHT / CELL_HEIGHT; ++j){
			Cell* cell = &mCells[i*WINDOW_WIDTH/CELL_WIDTH + WINDOW_HEIGHT/CELL_HEIGHT];
			
		}
	}
}

void World::render()
{
	mRenderSystem.render();
}

World::~World()
{
}

}
