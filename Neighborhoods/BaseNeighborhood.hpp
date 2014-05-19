#ifndef BASENEIGHBORHOOD_HPP
#define BASENEIGHBORHOOD_HPP

#include <memory>

namespace CA{

class BaseNeighborhood
{
public:
	enum Neighborhoods { ONE_D_THREE_CELL, ONE_D_FIVE_CELL, VON_NEUMANN, MOORE };
    Neighborhoods mNeighborhoodType;

	typedef std::vector<std::shared_ptr<CA::Cell> > CellArray;
	CellArray mCells;

	std::shared_ptr<CA::Cell> mCenter;	

	BaseNeighborhood(Neighborhoods hood, std::shared_ptr<CA::Cell> center) : mNeighborhoodType(hood), mCenter(center)
	{
	}

	virtual ~BaseNeighborhood()
	{
	}
};

}

#endif
