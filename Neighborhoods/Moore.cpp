#include "Moore.hpp"

namespace CA{

void Moore::init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
{
	/*MAKE A 3X3 NEIGHBORHOOD AROUND CENTER*/
    int startX = 0, endX = 0;
    int startY = 0, endY = 0;
    int x = arrayIndex_x;
    int y = arrayIndex_y;

    if(x > 0){
        if(x < GRIDCELL_WIDTH-1){
            startX = x - 1;
            endX = x + 1;
        }
        else if(x >= GRIDCELL_WIDTH-1){
            startX = x - 1;
            endX = x;
            mWidth--;
        }
    }
    else if(x <= 0){
        startX = x;
        endX = x + 1;
        mWidth--;
	}

    if(y > 0){
       if(y < GRIDCELL_HEIGHT-1){
            startY = y - 1;
            endY = y + 1;
        }
        else if(y >= GRIDCELL_HEIGHT-1){
            startY = y - 1;
            endY = y;
            mHeight--;
        }
    }
    else if(y <= 0){
        startY = y;
        endY = y + 1;
        mHeight--;
    }

	for(int i = 0; i < mWidth*mHeight; i++){
        mCells.push_back(std::make_shared<CA::Cell>(0, 0, false));
    }

    //from (x,y) to our local neighborhood of (i, j)
    int i = 0;
    int j = 0;

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
