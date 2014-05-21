#ifndef MOORE_HPP
#define MOORE_HPP

#include "BaseNeighborhood.hpp"

namespace CA{

const int MOORE_NEIGHBORHOOD_WIDTH = 3;
const int MOORE_NEIGHBORHOOD_HEIGHT = 3;

class Moore : public BaseNeighborhood
{
private:

public:
    Moore(std::shared_ptr<CA::Cell> center) : BaseNeighborhood(Neighborhoods::MOORE, center)
    {
		mCells.reserve(MOORE_NEIGHBORHOOD_WIDTH * MOORE_NEIGHBORHOOD_HEIGHT);
    }

	void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y)
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
    	    }
    	}
    	else if(x <= 0){
    	    startX = x;
    	    endX = x + 1;
 		}

		if(y > 0){
       	    if(y < GRIDCELL_HEIGHT-1){
        	    startY = y - 1;
        	    endY = y + 1;
        	}
       		else if(y >= GRIDCELL_HEIGHT-1){
        	    startY = y - 1;
        	    endY = y;
        	}
    	}
   	    else if(y <= 0){
        	startY = y;
    	    endY = y + 1;
	    }

		//from (x,y) to our local neighborhood of (i, j)
		int i = 0;
		int j = 0;

		for(; startX <= endX; startX++, i++){
			for(; startY <= endY; startY++, j++){
				insert_at(mCells, (i+j*3), cells[getIndexNeighborhood(x,y)]);
			}
			startY = y > 0 ? y-1 : y;
			j = 0;
		}
	}

	NeighborBitset update(float dTime)
	{
		
	}
		
    ~Moore()
    {
		mCells.clear();
    }
};

} 

#endif 
