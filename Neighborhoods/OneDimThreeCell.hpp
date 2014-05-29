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

	void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
	{
		//1x3 neighborhood around center
		int startX = 0, endX = 0;
		int startY = 0, endY = 1;
		int x = arrayIndex_x, y = arrayIndex_y;

		initBoundsOneDim(startX, startY, endX, endY, mWidth, mHeight, x, y);
		
		for(int i = 0; i < mWidth; i++){
			mCells.push_back(std::make_shared<CA::Cell>(0, 0, false));
		}

		int i = 0, j = 0;

		for(; startX <= endX; startX++, i++){
			for(; startY <= endY; startY++, j++){
				//getIndex works vertically but we're doing horizontal arrays, which is why we do getIndex(y, x). hackish, needs to be looked into
				mCells[i+j*mWidth] = cells[getIndex(startY, startX)];
			}
		}
	}

	NeighborBitset update(float dTime){};

	~OneDimThreeCell()
	{
		mCells.clear();
	}
};

} 

#endif
