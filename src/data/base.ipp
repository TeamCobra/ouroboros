#include <memory>

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
		mItems[apField->getTitle()] = apField;
	}
	
	template<class T>
	void group<T>::add(group<T> *apField)
	{
		//FIXME what if it is null?
		mGroups[apField->getTitle()] = apField;
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
		return const_cast<T *>(static_cast<const group&>(*this).findGroup(aName));
	}
	
	template<class T>
	const T *group<T>::findItem(const std::string& aName) const
	{
		if (mItems.count(aName))
		{
			return mItems.at(aName);
		}
		return nullptr;
	}
	
	template<class T>
	const group<T>* group<T>::findGroup(const std::string& aName) const
	{
		if (mItems.count(aName))
		{
			return mGroups.at(aName);
		}
		return nullptr;
	}

	template<class T>
	std::size_t group<T>::getSize() const
	{
		return mItems.size() + mGroups.size();
	}
}