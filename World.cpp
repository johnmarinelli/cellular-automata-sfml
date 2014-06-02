#include "World.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory>
namespace CA{

World::World(sf::RenderWindow& target) : mRenderSystem(target), mRuleSystem(CA::BaseNeighborhood::ONE_DIM_THREE_CELL)
{
	mCells.reserve(GRIDCELL_WIDTH * GRIDCELL_HEIGHT);
}

void World::init()
{
	std::ifstream rulesFile("Rules/OneDimThreeCell.txt");
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
	for(int i = 0; i < GRIDCELL_HEIGHT; ++i){
		for(int j = 0; j < GRIDCELL_WIDTH; ++j){
			mRuleSystem.initNeighborhoods(mCells, j, i);
		}
	}

//	mCells[getIndex(28, 0)]->setState(true);
	mCells[getIndex(30, 0)]->setState(true);
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
