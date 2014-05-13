#include "World.hpp"
#include <math.h>
#include <iostream>
#include <memory>

namespace CA{

int getIndex(int x, int y)
{
	return x + (y * WINDOW_HEIGHT/CELL_HEIGHT);
}

void updateCell(std::shared_ptr<Cell> cell, int x, int y, std::vector<std::shared_ptr<Cell> >& mCells)
{
	//make an array of cells around the first cell
	std::vector<Cell*> cells;

	int i = x > 0 ? x-1 : x;
	int j = y > 0 ? y-1 : y;
	
	int endX = x + 1;
	int endY = y + 1;

	int aliveNeighbors = 0;
	for(; i <= endX; i++){
		for(; j <= endY; j++){
			cells.push_back(mCells[getIndex(i, j)].get());
			if(cell.get() != mCells[getIndex(i, j)].get() && mCells[getIndex(i, j)]->getState()){
				printf("i'm an alive neighbor\n");
				aliveNeighbors++;
			}
		}
		j = 0;
	}

	if(cell->getState()){
		if(aliveNeighbors < 2){
			cell->setState(false);
		}
		else if(aliveNeighbors > 3){
			cell->setState(false);
		}
	}
	
	else if(!cell->getState()){
		if(aliveNeighbors == 3){
			cell->setState(true);
		}
	}	
}

World::World(sf::RenderWindow& target) : mRenderSystem(target)
{
	mCells.reserve(std::ceil(WINDOW_WIDTH / CA::CELL_WIDTH) * std::ceil(WINDOW_HEIGHT / CA::CELL_HEIGHT));
}

void World::init()
{
	for(int i = 0; i < WINDOW_WIDTH; i+=CA::CELL_WIDTH){
		for(int j = 0; j < WINDOW_HEIGHT; j+=CA::CELL_HEIGHT){
			auto cell = std::make_shared<Cell>(i, j, false);
			mCells.push_back(cell);
			mRenderSystem.addCell(cell);
		}
	}

	mCells[getIndex(0, 0)]->setState(true);
	mCells[getIndex(1, 0)]->setState(true);
	mCells[getIndex(1, 1)]->setState(true);

	std::cout << "world::init" << mCells.size() << " " << std::endl;
}

void World::update(float dTime)
{
	for(int i = 0; i < WINDOW_WIDTH / CELL_WIDTH; ++i){
		for(int j = 0; j < WINDOW_HEIGHT / CELL_HEIGHT; ++j){
			auto cell = mCells[getIndex(i, j)];
			updateCell(cell, i, j, mCells);
		}
	}
}

void World::render()
{
	mRenderSystem.render();
}

World::~World()
{
	mCells.clear();
}

}
