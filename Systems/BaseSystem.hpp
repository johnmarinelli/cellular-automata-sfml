#ifndef BASESYSTEM_HPP
#define BASESYSTEM_HPP

#include <vector>
#include <memory>

namespace CA{

class BaseSystem
{
public:
	typedef std::vector<std::shared_ptr<CA::Cell> > CellArray;

	BaseSystem()
	{
	}
	
	virtual ~BaseSystem()
	{
	}
};

}

#endif
