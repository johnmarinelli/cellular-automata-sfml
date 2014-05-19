#ifndef 1D3C_HPP
#define 1D3C_HPP

#include "BaseNeighborhood.hpp";

namespace CA{

class OneDimThreeCell : public BaseNeighborhood
{
private:

public:
	OneDimThreeCell(Neighborhoods hood) : BaseNeighborhood(hood)
	{
	}

	~OneDimThreeCell()
	{
	}
};

} 

#endif
