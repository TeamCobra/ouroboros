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
		if (apField)
		{
			//Create a new string for lookup purposes with all lower case letters and no spaces
			std::string lookupTitle = apField->getTitle();
			std::transform(lookupTitle.begin(), lookupTitle.end(), lookupTitle.begin(), ::tolower);
			std::replace(lookupTitle.begin(), lookupTitle.end(), ' ', '_');
			mItems[lookupTitle] = apField;
			
			mInsertOrder.push_back(lookupTitle);
		}
	}
	
	template<class T>
	void group<T>::add(group<T> *apGroup)
	{
		if (apGroup)
		{
			//Create a new string for lookup purposes with all lower case letters and no spaces
			std::string lookupTitle = apGroup->getTitle();
			std::transform(lookupTitle.begin(), lookupTitle.end(), lookupTitle.begin(), ::tolower);
			std::replace(lookupTitle.begin(), lookupTitle.end(), ' ', '_');
			mGroups[lookupTitle] = apGroup;
			
			mInsertOrder.push_back(lookupTitle);
		}
	}
	
	template<class T>
	T *group<T>::removeItem(const std::string& aName)
	{
		T *result = NULL;
		if (mItems.count(aName))
		{
			result = mItems.at(aName);
			mItems.erase(aName);
			mInsertOrder.remove(aName);
		}
		return result;
	}

	template<class T>
	group<T> *group<T>::removeGroup(const std::string& aName)
	{
		group<T> *result = NULL;
		if (mGroups.count(aName))
		{
			result = mGroups.at(aName);
			mGroups.erase(aName);
			mInsertOrder.remove(aName);
		}
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
		
		result += "\"type\" : \"group\"";
		
		std::string base = base_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);
		
		result += ", " + base;
		
		
		result += ", \"contents\" : {";
		if (!(mGroups.empty() && mItems.empty()))
		{
			typedef std::list<std::string>::const_iterator l_iter;
			
			for (l_iter itr = mInsertOrder.begin(); itr != mInsertOrder.end(); ++itr)
			{
				if (mGroups.count(*itr))
				{
					result += " \"" + *itr + "\" : " + mGroups.find(*itr)->second->getJSON() + ",";
				}
				if (mItems.count(*itr))
				{
					result +=  "\"" + *itr + "\" : " + mItems.find(*itr)->second->getJSON() + ",";
				}
			}
			
			if (!(mGroups.empty() && mItems.empty()))
			{
				result.erase(result.end()-1);
			}
		}
		
		result += " } }";
		return result;
	}
	
}
