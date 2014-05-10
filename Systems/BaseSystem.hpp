#ifndef BASESYSTEM_HPP
#define BASESYSTEM_HPP

#include <vector>

namespace CA{

class BaseSystem
{
public:
	typedef std::vector<CA::Cell> CellArray;

	BaseSystem()
	{
	}
	
	virtual ~BaseSystem()
	{
	}
};

}

#endif
