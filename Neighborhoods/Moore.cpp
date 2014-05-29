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

    for(; startY <= endY; startY++, i++){
        for(; startX <= endX; startX++, j++){
            mCells[i+j*mWidth] = cells[getIndex(startX, startY)];
        }
        startX = x > 0 ? x-1 : x;
        j = 0;
    }
}

BaseNeighborhood::NeighborBitset Moore::update(float dTime)
{
	NeighborBitset neighbors;
    neighbors.reserve(mHeight);
    std::vector<CA::State> bitLine;
    bitLine.reserve(mWidth);

    for(int i = 0; i < mHeight; i++){
        bitLine.clear();
        for(int j = 0; j < mWidth; j++){
            if(mCells[i+j*mHeight].get() == mCenter.get()){
               bitLine.push_back(CA::State::OFF);
            }
            else{
                bitLine.push_back(mCells[i+j*mHeight]->getState() == true ? CA::State::ON : CA::State::OFF);
            }
        }
        neighbors.push_back(bitLine);
    }

    return neighbors;
}

}
