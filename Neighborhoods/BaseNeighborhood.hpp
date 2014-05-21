#ifndef BASENEIGHBORHOOD_HPP
#define BASENEIGHBORHOOD_HPP

#include "../Utilities.hpp"
#include <memory>

namespace CA{

const int GRIDCELL_WIDTH = WINDOW_WIDTH / CA::CELL_WIDTH;
const int GRIDCELL_HEIGHT = WINDOW_HEIGHT / CA::CELL_HEIGHT;

class BaseNeighborhood
{
public:

//remember to remove the getIndex in world.cpp
int getIndexNeighborhood(int x, int y)
{
    return y + (x * GRIDCELL_HEIGHT);
}


	enum Neighborhoods { ONE_D_THREE_CELL, ONE_D_FIVE_CELL, VON_NEUMANN, MOORE };
    Neighborhoods mNeighborhoodType;

	typedef std::vector<std::shared_ptr<CA::Cell> > CellArray;
	CellArray mCells;

	std::shared_ptr<CA::Cell> mCenter;	

	BaseNeighborhood(Neighborhoods hood, std::shared_ptr<CA::Cell> center) : mNeighborhoodType(hood), mCenter(center)
	{
	}
	
	virtual void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y) = 0;

	virtual ~BaseNeighborhood()
	{
		mCells.clear();
	}
};

}

#endif
