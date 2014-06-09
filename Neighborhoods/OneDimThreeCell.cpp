#include "OneDimThreeCell.hpp"

namespace CA{

void OneDimThreeCell::init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
{
        //1x3 neighborhood around center
        int startX = 0, endX = 0;
        int startY = 0, endY = 0;
        int x = arrayIndex_x, y = arrayIndex_y;

        initBoundsOneDim(startX, startY, endX, endY, mWidth, mHeight, x, y);

        for(int i = 0; i < mWidth; i++){
		mCells.push_back(std::make_shared<CA::Cell>(0, 0, false));
        }

        int i = 0, j = 0;

        for(; startY <= endY; startY++, i++){
                for(; startX <= endX; startX++, j++){
        		mCells[j] = cells[getIndex(startX, startY)];
                }
        }
}

BaseNeighborhood::NeighborBitset OneDimThreeCell::update(float dTime)
{
        NeighborBitset neighbors;
        std::vector<CA::State> bitLine;
        bitLine.reserve(ONEDIMTHREECELL_NEIGHBORHOOD_WIDTH);

        for(int i = 0; i < mHeight; i++){
                for(int j = 0; j < mWidth; j++){
                        if(mCells[i+j].get() == mCenter.get()){
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
