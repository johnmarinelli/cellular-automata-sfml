#ifndef ONEDIMFIVECELL_HPP
#define ONEDIMFIVECELL_HPP

#include "BaseNeighborhood.hpp"

namespace CA{

const int ONEDIMFIVECELL_NEIGHBORHOOD_WIDTH = 5;
const int ONEDIMFIVECELL_NEIGHBORHOOD_HEIGHT = 1;

class OneDimFiveCell : public BaseNeighborhood
{
private:

public:
    OneDimFiveCell(std::shared_ptr<CA::Cell> center) : BaseNeighborhood(Neighborhoods::ONE_DIM_FIVE_CELL, center, ONEDIMFIVECELL_NEIGHBORHOOD_WIDTH, ONEDIMFIVECELL_NEIGHBORHOOD_HEIGHT)
    {
	mCells.reserve(ONEDIMFIVECELL_NEIGHBORHOOD_HEIGHT);
    }

    void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
    {
        //1x5 neighborhood around center
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

    NeighborBitset update(float dTime)
    {
        NeighborBitset neighbors;
        std::vector<CA::State> bitLine;
        bitLine.reserve(ONEDIMFIVECELL_NEIGHBORHOOD_WIDTH);

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

    ~OneDimFiveCell()
    {
	mCells.clear();
    }
};

} 

#endif 
