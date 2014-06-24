#include "World.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory>

namespace CA{

World::World(sf::RenderWindow& target) : mPopulation(0), mGeneration(0), mRenderSystem(target, mPopulation, mGeneration), mRuleSystem(CA::BaseNeighborhood::VON_NEUMANN)
{
	mCells.reserve(GRIDCELL_WIDTH * GRIDCELL_HEIGHT);
}

void World::seedWorld()
{
/*
	mCells[getIndex(0, 2)]->setState(true);
    mCells[getIndex(1, 2)]->setState(true);
    mCells[getIndex(2, 2)]->setState(true);
    mCells[getIndex(2, 1)]->setState(true);
    mCells[getIndex(1, 0)]->setState(true);

    mCells[getIndex(30, 4)]->setState(true);
    mCells[getIndex(31, 4)]->setState(true);
    mCells[getIndex(32, 4)]->setState(true);
    mCells[getIndex(30, 3)]->setState(true);
    mCells[getIndex(31, 2)]->setState(true);

	mCells[getIndex(0, 8)]->setState(true);
    mCells[getIndex(1, 8)]->setState(true);
    mCells[getIndex(2, 8)]->setState(true);
    mCells[getIndex(2, 7)]->setState(true);
    mCells[getIndex(1, 6)]->setState(true);

    mCells[getIndex(60, 4)]->setState(true);
    mCells[getIndex(61, 4)]->setState(true);
    mCells[getIndex(62, 4)]->setState(true);
    mCells[getIndex(60, 3)]->setState(true);
    mCells[getIndex(61, 2)]->setState(true);

    mCells[getIndex(30, 30)]->setState(true);
    mCells[getIndex(30, 29)]->setState(true);
    mCells[getIndex(31, 29)]->setState(true);
    mCells[getIndex(30, 31)]->setState(true);
    mCells[getIndex(29, 30)]->setState(true);*/

    mCells[getIndex(1, 1)]->setState(true);
    mCells[getIndex(2, 2)]->setState(true);
}

void World::init()
{
	std::ifstream rulesFile("Rules/VonNeumann.txt");
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

    seedWorld();
}

void World::update(float dTime)
{
	mRuleSystem.update(dTime);

	for(auto cell : mCells){
		cell->update(dTime);
	}

    mGeneration++;
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
