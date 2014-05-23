#include "World.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory>

namespace CA{

int getIndex(int x, int y)
{
	return y + (x * GRIDCELL_HEIGHT);
}

void updateCell(std::shared_ptr<Cell> cell, int x, int y, std::vector<std::shared_ptr<Cell> >& mCells)
{
	//make an array of cells around the first cell
	std::vector<Cell*> cells;

	int i = 0, endX = 0;
	int j = 0, endY = 0;

	if(x > 0){
		if(x < GRIDCELL_WIDTH-1){
			i = x - 1;
			endX = x + 1;
		}
		else if(x >= GRIDCELL_WIDTH-1){
			i = x - 1;
			endX = x;
		}
	}
	else if(x <= 0){
		i = x;
		endX = x + 1;
	}

	if(y > 0){
		if(y < GRIDCELL_HEIGHT-1){
			j = y - 1;
			endY = y + 1;
		}
		else if(y >= GRIDCELL_HEIGHT-1){
			j = y - 1;
			endY = y;
		}
	}
	else if(y <= 0){
		j = y;
		endY = y + 1;
	}
/*
	i = x > 0 ? (x < GRIDCELL_WIDTH ? x : x - 1) : x;
	j = y > 0 ? (y < GRIDCELL_HEIGHT ? y : y - 1) : y;
	
	endX = i > 0 ? (i < GRIDCELL_WIDTH - 1 ? i + 1 : i) : i;
	endY = j > 0 ? (j < GRIDCELL_HEIGHT - 1 ? j + 1 : j) : j;
*/
	int aliveNeighbors = 0;

	for(; i <= endX; i++){
		for(; j <= endY; j++){
			cells.push_back(mCells[getIndex(i, j)].get());
		}
		j = y > 0 ? y - 1 : y;
	}

	for(auto neighbor : cells){
		if(neighbor->getState() && cell.get() != neighbor){
			aliveNeighbors++;
		}
	}

	if(cell->getState()){
		if(aliveNeighbors < 2){
			cell->setState(false);
		}
		else if(aliveNeighbors > 3){
			cell->setState(false);
		}
		else if(aliveNeighbors == 2 || aliveNeighbors == 3){
			cell->setState(true);
		}
	}
	
	else if(!cell->getState()){
		if(aliveNeighbors == 3){
			cell->setState(true);
		}
	}	

	if(aliveNeighbors > 0){	
	printf("alive neighbors: %d\n", aliveNeighbors);
	}
}

World::World(sf::RenderWindow& target) : mRenderSystem(target), mRuleSystem(CA::BaseNeighborhood::MOORE)
{
	mCells.reserve(GRIDCELL_WIDTH * GRIDCELL_HEIGHT);
}

void World::init()
{
	std::ifstream rulesFile("Rules/Conway.txt");
	mRuleSystem.initRules(rulesFile);

	//push shared ptr in mCells, and send it to rulesystem to make a neighborhood
	for(int i = 0; i < WINDOW_WIDTH; i+=CA::CELL_WIDTH){
		for(int j = 0; j < WINDOW_HEIGHT; j+=CA::CELL_HEIGHT){
			auto cell = std::make_shared<Cell>(i, j, false);
			mCells.push_back(cell);
			mRenderSystem.addCell(cell);
			mRuleSystem.addNeighborhood(cell);
		}
	}

	//initialize all the neighborhoods AFTER our mCells is complete
	for(int i = 0; i < GRIDCELL_WIDTH; ++i){
		for(int j = 0; j < GRIDCELL_HEIGHT; ++j){
			mRuleSystem.initNeighborhoods(mCells, i, j);
		}
	}

	mCells[getIndex(3, 1)]->setState(true);
	mCells[getIndex(3, 2)]->setState(true);
	mCells[getIndex(3, 3)]->setState(true);
	mCells[getIndex(3, 4)]->setState(true);
}

void World::update(float dTime)
{
	for(int i = 0; i < GRIDCELL_WIDTH; ++i){
		for(int j = 0; j < GRIDCELL_HEIGHT; ++j){
			auto cell = mCells[getIndex(i, j)];
			updateCell(cell, i, j, mCells);
		}
	}

	for(auto cell : mCells){
		cell->update(0);
	}

	mRuleSystem.update(dTime);
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
