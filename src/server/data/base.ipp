#include <memory>
#include <algorithm>

namespace ouroboros
{
	template<class T>
	group<T>::group(const std::string& aTitle, const std::string& aDescription)
	:base_field(aTitle, aDescription)
	{}
	
	template<class T>
	void group<T>::add(T *apField)
	{
		//FIXME What if it is null?
		//Create a new string for lookup purposes with all lower case letters and no spaces
		std::string lookupTitle = apField->getTitle();
		std::transform(lookupTitle.begin(), lookupTitle.end(), lookupTitle.begin(), ::tolower);
		std::replace(lookupTitle.begin(), lookupTitle.end(), ' ', '_');
		mItems[lookupTitle] = apField;
	}
	
	template<class T>
	void group<T>::add(group<T> *apField)
	{
		//FIXME what if it is null?
		//Create a new string for lookup purposes with all lower case letters and no spaces
		std::string lookupTitle = apField->getTitle();
		std::transform(lookupTitle.begin(), lookupTitle.end(), lookupTitle.begin(), ::tolower);
		std::replace(lookupTitle.begin(), lookupTitle.end(), ' ', '_');
		mGroups[lookupTitle] = apField;
	}
	
	template<class T>
	T *group<T>::removeItem(const std::string& aName)
	{
		//FIXME Should this throw an exception?
		T *result = mItems.at(aName);
		mItems.erase(aName);
		return result;
	}

	template<class T>
	group<T> *group<T>::removeGroup(const std::string& aName)
	{
		//FIXME Should this throw an exception?
		group<T> *result = mGroups.at(aName);
		mGroups.erase(aName);
		return result;
	}
	
	template<class T>
	T *group<T>::findItem(const std::string& aName)
	{
		return const_cast<T *>(static_cast<const group&>(*this).findItem(aName));
	}
	
	template<class T>
	group<T>* group<T>::findGroup(const std::string& aName)
	{	
		return const_cast<group<T> *>(static_cast<const group&>(*this).findGroup(aName));
	}
	
	template<class T>
	const T *group<T>::findItem(const std::string& aName) const
	{
		if (mItems.count(aName))
		{
			return mItems.at(aName);
		}
		return NULL;
	}
	
	template<class T>
	const group<T>* group<T>::findGroup(const std::string& aName) const
	{
		if (mGroups.count(aName))
		{
			return mGroups.at(aName);
		}
		return NULL;
	}
	
	template<class T>
	std::size_t group<T>::getSize() const
	{
		return mItems.size() + mGroups.size();
	}
	
	template<class T>
	std::string group<T>::getJSON() const
	{
		std::string result = "{ ";
		
		for (typename std::map<std::string, group<T>*>::const_iterator itr = mGroups.begin(); itr != mGroups.end(); itr++)
		{
			result += "\"" + itr->first + "\" : " + itr->second->getJSON() + ",";
		}
		if (!mGroups.empty() && mItems.empty())
		{
			result.erase(result.end()-1);
		}
		
		for (typename std::map<std::string, T*>::const_iterator itr = mItems.begin(); itr != mItems.end(); itr++)
		{
			result += "\"" + itr->first + "\" : " + itr->second->getJSON() + ",";
		}
		if (!mItems.empty())
		{
			result.erase(result.end()-1);		
		}
		
		result += " }";
		return result;
	}
}
