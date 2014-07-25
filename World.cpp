#include "World.hpp"
#include <math.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <algorithm>

namespace CA{

World::World(sf::RenderWindow& target) : mPopulation(0), mGeneration(0), mRenderSystem(target, mPopulation, mGeneration), mRuleSystem(CA::BaseNeighborhood::MOORE)
{
	mCells.reserve(GRIDCELL_WIDTH * GRIDCELL_HEIGHT);
}

void World::seedWorld(char* input)
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
*/
    std::ifstream seedFile(input);
    if(!seedFile){
        std::cerr << "Couldn't open seed file: " << input << std::endl;
    }
    else{
        std::string coordinates;

        while(!seedFile.eof()){
            std::getline(seedFile, coordinates);
            coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), ' '), coordinates.end());
            std::size_t hasComma = coordinates.find(",");
            if(hasComma != std::string::npos){
                int x = std::stoi(coordinates.substr(0, hasComma));
                int y = std::stoi(coordinates.substr(hasComma+1));

                mCells[getIndex(x, y)]->setState(true);
            }
            else{
                std::cerr << "Malformed coordinate: " << coordinates << " in " << input << std::endl;
            }
        }
    }
}

void World::init(char* input[])
{
	std::ifstream rulesFile(input[1]);
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

    seedWorld(input[2]);
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
