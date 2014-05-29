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
    Moore(std::shared_ptr<CA::Cell> center) : BaseNeighborhood(Neighborhoods::MOORE, center, MOORE_NEIGHBORHOOD_WIDTH, MOORE_NEIGHBORHOOD_HEIGHT)
    {
		mCells.reserve(MOORE_NEIGHBORHOOD_WIDTH * MOORE_NEIGHBORHOOD_HEIGHT);
    }

	void init(std::vector<std::shared_ptr<CA::Cell> >& cells, int arrayIndex_x, int arrayIndex_y);

	NeighborBitset update(float dTime);

    ~Moore()
    {
		mCells.clear();
    }
};

} 

#endif 
