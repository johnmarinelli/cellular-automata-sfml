#include "Moore.hpp"

namespace CA{

void Moore::init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
{
	int startX = 0, endX = 0;
	int startY = 0, endY = 0;
	int x = arrayIndex_x, y = arrayIndex_y;
	initBoundsTwoDim(startX, startY, endX, endY, mWidth, mHeight, x, y);

	for(int i = 0; i < mWidth*mHeight; i++){
        mCells.push_back(std::make_shared<CA::Cell>(0, 0, false));
    }

    //from (x,y) to our local neighborhood of (i, j)
    int i = 0, j = 0;

    for(; startX <= endX; startX++, i++){
        for(; startY <= endY; startY++, j++){
            mCells[i+j*mWidth] = cells[getIndex(startX, startY)];
        }
        startY = y > 0 ? y-1 : y;
        j = 0;
    }
}

BaseNeighborhood::NeighborBitset Moore::update(float dTime)
{
	NeighborBitset neighbors;
    neighbors.reserve(mHeight);
    std::vector<CA::State> bitLine;
    bitLine.reserve(mWidth);

    for(int i = 0; i < mWidth; i++){
        bitLine.clear();
        for(int j = 0; j < mHeight; j++){
            if(mCells[i+j*mWidth].get() == mCenter.get()){
               bitLine.push_back(CA::State::OFF);
            }
            else{
                bitLine.push_back(mCells[i+j*mWidth]->getState() == true ? CA::State::ON : CA::State::OFF);
            }
        }
        neighbors.push_back(bitLine);
    }

    return neighbors;
}

}
