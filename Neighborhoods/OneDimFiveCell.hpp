#ifndef 1D5C_HPP
#define 1D5C_HPP

#include "BaseNeighborhood.hpp";

namespace CA{

class OneDimFiveCell : public BaseNeighborhood
{
private:

public:
    OneDimFiveCell(Neighborhoods hood) : BaseNeighborhood(hood)
    {
    }

    ~OneDimFiveCell()
    {
    }
};

} 

#endif 
