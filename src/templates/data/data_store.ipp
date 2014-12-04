#include "data_store.hpp"

namespace ouroboros
{
		template<class T>
		data_store<T>::data_store(group<T>&& aRoot)
		:mRoot(std::move(aRoot))
		{}

		namespace detail
		{
			std::vector<std::string> split(const std::string& aString, const std::string& aDelim)
			{
				//FIXME this returns empty strings if there are consecutive delims
				std::vector<std::string> result;
				std::size_t end = std::string::npos, start = 0;
				while ((end = aString.substr(start, end).find(aDelim)) != std::string::npos)
				{
					result.push_back(aString.substr(start, end));
					start = end + aDelim.length();
				}
				result.push_back(aString.substr(start, end));
				
				return result;
			}
		}

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
			result = mRoot.findGroup(groups.front());

			for (std::size_t index = 1; (result && (index < groups.size())); ++index)
			{
				result = mRoot.findGroup(groups[index]);
			}
			return result;
		}
}
