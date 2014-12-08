#include "data_store.hpp"
#include "misc.h"

namespace ouroboros
{
	template<class T>
	data_store<T>::data_store(group<T>&& aRoot)
	:mRoot(std::move(aRoot))
	{}

	template <class T>
	T *data_store<T>::get(const std::string& aName, const std::string& aGroup)
	{
		group<T> *pGroup = this->get(aGroup);

		if (pGroup == nullptr)
		{
			return nullptr;
		}

		var_field *field = pGroup->findItem(aName);

		return field;
	}

	template <class T>
	group<T>* data_store<T>::get(const std::string& aGroup)
	{
		group<T>* result;
		//Check that the group string is valid syn
		//Break aGroup into tokens
		std::vector<std::string> groups = detail::split(aGroup, "-");
		
		//In case we're trying to access the root group
		if (groups.size() == 1)
		{
			if (mRoot.getTitle() == groups.front())
			{
				return &mRoot;
			}
			return nullptr;
		}
		
		result = mRoot.findGroup(groups.front());

		for (std::size_t index = 1; (result && (index < groups.size())); ++index)
		{
			result = mRoot.findGroup(groups[index]);
		}
		return result;
	}
}
