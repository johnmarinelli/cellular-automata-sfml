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

		/*MAKE A 3X3 NEIGHBORHOOD AROUND CENTER*/
    }

    ~Moore()
    {
		mCells.clear();
    }
};

} 

#endif 
