#ifndef ONEDIMTHREECELL_HPP
#define ONEDIMTHREECELL_HPP

#include "BaseNeighborhood.hpp"

namespace CA{

const int ONEDIMTHREECELL_NEIGHBORHOOD_WIDTH = 3;
const int ONEDIMTHREECELL_NEIGHBORHOOD_HEIGHT = 1;

class OneDimThreeCell : public BaseNeighborhood
{
private:

public:
	OneDimThreeCell(std::shared_ptr<CA::Cell> center) : BaseNeighborhood(Neighborhoods::ONE_DIM_THREE_CELL, center, ONEDIMTHREECELL_NEIGHBORHOOD_WIDTH, ONEDIMTHREECELL_NEIGHBORHOOD_HEIGHT)
	{
		mCells.reserve(ONEDIMTHREECELL_NEIGHBORHOOD_WIDTH);
	}

	void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y);

	NeighborBitset update(float dTime);

	~OneDimThreeCell()
	{
		mCells.clear();
	}
};

} 

#endif
