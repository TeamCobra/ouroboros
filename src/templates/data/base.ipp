#include <memory>

namespace ouroboros
{
	template<class T>
	group<T>::group(const std::string& aTitle, const std::string& aDescription)
	:base_field(aTitle, aDescription)
	{}
	
	template<class T>
	void group<T>::add(T&& aField)
	{
		mItems[aField.getTitle()] = aField;
	}
	
	template<class T>
	void group<T>::add(group<T>&& aField)
	{
		mGroups[aField.getTitle()] = aField;
	}
	
	template<class T>
	T&& group<T>::removeItem(const std::string& aName)
	{
		//FIXME Should this throw an exception?
		T result = std::move(mItems.at(aName));
		mItems.erase(aName);
		return std::move(result);
	}

	template<class T>
	group<T>&& group<T>::removeGroup(const std::string& aName)
	{
		//FIXME Should this throw an exception?
		group<T> result = std::move(mGroups.at(aName));
		mGroups.erase(aName);
		return std::move(result);
	}
	
	template<class T>
	T *group<T>::findItem(const std::string& aName) const
	{
		if (mItems.count(aName))
		{
			return &mItems.at(aName);
		}
		return nullptr;
	}
	
	template<class T>
	group<T>* group<T>::findGroup(const std::string& aName) const
	{
		if (mItems.count(aName))
		{
			return &mGroups.at(aName);
		}
		return nullptr;
	}

	template<class T>
	std::size_t group<T>::getSize() const
	{
		return mItems.size() + mGroups.size();
	}
}