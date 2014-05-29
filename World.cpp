#include "World.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory>
namespace CA{

World::World(sf::RenderWindow& target) : mRenderSystem(target), mRuleSystem(CA::BaseNeighborhood::MOORE)
{
	mCells.reserve(GRIDCELL_WIDTH * GRIDCELL_HEIGHT);
}

void World::init()
{
	std::ifstream rulesFile("Rules/Conway.txt");
	mRuleSystem.initRules(rulesFile);

	//push shared ptr in mCells, and send it to rulesystem to make a neighborhood
	for(int i = 0; i < WINDOW_HEIGHT; i+=CA::CELL_HEIGHT){
		for(int j = 0; j < WINDOW_WIDTH; j+=CA::CELL_WIDTH){
			auto cell = std::make_shared<Cell>(j, i, false);
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
	mRuleSystem.update(dTime);

	for(auto cell : mCells){
		cell->update(dTime);
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
