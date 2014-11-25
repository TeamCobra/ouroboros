#ifndef _OUROBOROS_DATASTORE_H_
#define _OUROBOROS_DATASTORE_H_

#include "base.hpp"
#include <string>

namespace ouroboros
{
	class data_store
	{
	public:
		data_store(group aRoot);
		base_field *get(const std::string& aName, const std::string& aGroup);
		
	private:
		group mRoot;
	};

}

#endif//_OUROBOROS_DATASTORE_H_