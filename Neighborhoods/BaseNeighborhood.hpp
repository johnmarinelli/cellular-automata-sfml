#ifndef BASENEIGHBORHOOD_HPP
#define BASENEIGHBORHOOD_HPP

#include "../Config.hpp"
#include "../Cell.hpp"
#include <memory>
#include <vector>

namespace CA{

template<typename T>
T& insert_at(T& container, size_t index, const typename T::value_type& value)
{
	container.insert(container.begin() + index, value);
	return container;
}

inline void initBoundsOneDim(int& startX, int& startY, int&endX, int& endY,
uint8_t& width, uint8_t& height, int arrayIndex_x, int arrayIndex_y)
{
	int x = arrayIndex_x;
	int y = arrayIndex_y;

	int horizontalWidth = width / 2;

	if(x - horizontalWidth > 0){
	    //normal; position is somewhere between bounds
            if(x + horizontalWidth < GRIDCELL_WIDTH-1){
                startX = x - horizontalWidth;
                endX = x + horizontalWidth;
            }
	    //on the right hand side edge
            else if(x + horizontalWidth >= GRIDCELL_WIDTH-1){
		uint8_t difference = (x+horizontalWidth) - (GRIDCELL_WIDTH-1);

                startX = x - horizontalWidth;
                endX = GRIDCELL_WIDTH-1;
                width -= difference;
            }
        }

	//on the left hand side edge
        else if(x - horizontalWidth <= 0){
	    uint8_t difference = horizontalWidth - x;

            startX = 0;
            endX = x + horizontalWidth;
            width -= difference;
        }

	//since it's 1D, we just check if we've reached the bottom of the screen and cap if we have.
    if(y >= GRIDCELL_HEIGHT-1){
		endY = 0;
		height = 0;
   	}
	else{
		startY = arrayIndex_y;
		endY = startY + 1;
		height = 1;
	} 
}
/*
inline void initBoundsOneDim_ORIG(int& startX, int& startY, int&endX, int& endY,
uint8_t& width, uint8_t& height, int arrayIndex_x, int arrayIndex_y)
{
	int x = arrayIndex_x;
	int y = arrayIndex_y;

	int horizontalWidth = width / 2;

	//what if it's one cell away from an edge, and we're making 1x5 neighborhoods? then we need 1 neighbor on one side & 2 on other
	if(x > 0){
        if(x < GRIDCELL_WIDTH-1){
            startX = x - horizontalWidth;
            endX = x + horizontalWidth;
        }
        else if(x >= GRIDCELL_WIDTH-1){
            startX = x - horizontalWidth;
            endX = x;
            width--;
        }
    }
    else if(x <= 0){
        startX = x;
        endX = x + horizontalWidth;
        width--;
    }

	//since it's 1D, we just check if we've reached the bottom of the screen and cap if we have.
    if(y >= GRIDCELL_HEIGHT-1){
		endY = 0;
		height = 0;
   	}
	else{
		startY = arrayIndex_y;
		endY = startY + 1;
		height = 1;
	} 
}
*/

inline void initBoundsTwoDim(int& startX, int& startY, int& endX, int& endY, uint8_t& width, uint8_t& height, int arrayIndex_x, int arrayIndex_y)
{
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
            width--;
        }
    }
    else if(x <= 0){
        startX = x;
        endX = x + 1;
        width--;
    }

    if(y > 0){
       if(y < GRIDCELL_HEIGHT-1){
            startY = y - 1;
            endY = y + 1;
        }
        else if(y >= GRIDCELL_HEIGHT-1){
            startY = y - 1;
            endY = y;
            height--;
        }
    }
    else if(y <= 0){
        startY = y;
        endY = y + 1;
        height--;
    }

}

class BaseNeighborhood
{
public:
	typedef std::vector<std::vector<CA::State> > NeighborBitset;

	enum Neighborhoods { ONE_DIMENSION, ONE_DIM_THREE_CELL, ONE_DIM_FIVE_CELL, VON_NEUMANN, MOORE };
    Neighborhoods mNeighborhoodType;
	uint8_t mWidth;
	uint8_t mHeight;

	typedef std::vector<std::shared_ptr<CA::Cell> > CellArray;
	CellArray mCells;

	std::shared_ptr<CA::Cell> mCenter;	

	BaseNeighborhood(Neighborhoods hood, std::shared_ptr<CA::Cell> center, int width, int height) : mNeighborhoodType(hood), mCenter(center), mWidth(width), mHeight(height)
	{
	}
	
	virtual void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y) = 0;

	virtual NeighborBitset update(float dTime) = 0;

	virtual ~BaseNeighborhood()
	{
		mCells.clear();
	}
};

}

#endif
