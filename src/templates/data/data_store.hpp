#ifndef _OUROBOROS_DATASTORE_H_
#define _OUROBOROS_DATASTORE_H_

#include "base.hpp"
#include <string>
#include <vector>

namespace ouroboros
{
	template <class T>
	class data_store
	{
	public:
		data_store() = delete;
		data_store(group<T>&& aRoot);
		var_field *get(const std::string& aName, const std::string& aGroup);
		group<T> *get(const std::string& aGroup);

	private:
		group<T> mRoot;
	};

}

#include "data_store.ipp"

#endif//_OUROBOROS_DATASTORE_H_
