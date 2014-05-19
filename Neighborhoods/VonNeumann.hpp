#ifndef VONNEUMANN_HPP
#define VONNEUMANN_HPP

#include "BaseNeighborhood.hpp"

namespace CA{

class VonNeumann : public BaseNeighborhood
{
private:

public:
    VonNeumann() : BaseNeighborhood(VON_NEUMANN)
    {
    }

    ~VonNeumann()
    {
    }
};

} 

#endif 
