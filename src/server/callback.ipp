#include <string>

namespace ouroboros
{
	template <typename Item, typename Func>
	callback<Item, Func>::callback(Item aItem, Func aFunc)
	:mItem(aItem), mFunc(aFunc)
	{}
		
	template <typename Item, typename Func>
	void callback<Item, Func>::operator()() const
	{
		mFunc(mItem);
	}
	
	template <typename Item, typename Func>
	id_callback<Item, Func>::id_callback(const std::string& aId, Item aItem, Func aFunc)
	:callback<Item, Func>(aItem, aFunc), mId(aId)
	{}
	
	template <typename Item, typename Func>
	std::string id_callback<Item, Func>::get_id() const
	{
		return mId;
	}
	
}
