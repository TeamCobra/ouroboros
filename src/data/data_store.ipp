#include "data_store.hpp"
#include "misc.h"

namespace ouroboros
{
	template<class T>
	data_store<T>::data_store(group<T>&& aRoot)
	:mRoot(std::move(aRoot))
	{}

	template <class T>
	T *data_store<T>::get(const std::string& aGroup, const std::string& aName)
	{
		return const_cast<T *>(static_cast<const data_store&>(*this).get(aGroup, aName));
	}
	
	template <class T>
	const T *data_store<T>::get(const std::string& aGroup, const std::string& aName) const
	{
		const group<T> *pGroup = this->get(aGroup);

		if (pGroup == nullptr)
		{
			return nullptr;
		}

		const var_field *field = pGroup->findItem(aName);

		return field;
	}

	template <class T>
	group<T>* data_store<T>::get(const std::string& aGroup)
	{
		return const_cast<group<T> *>(static_cast<const data_store&>(*this).get(aGroup));
	}
	
	template <class T>
	const group<T>* data_store<T>::get(const std::string& aGroup) const
	{
		const group<T>* result = nullptr;
		//Check that the group string is valid syn
		//Break aGroup into tokens
		std::vector<std::string> groups = detail::split(aGroup, "-");
		
		
		if (!groups.empty())
		{
			//In case we're trying to access the root group
			if (mRoot.getTitle() == groups.front())
			{
				if (groups.size() == 1)
				{
					return &mRoot;
				}
				
				result = mRoot.findGroup(groups[1]);
				
				for (std::size_t index = 2; (result && (index < groups.size())); ++index)
				{
					result = result->findGroup(groups[index]);
				}
			}
		}
		return result;
	}
}
