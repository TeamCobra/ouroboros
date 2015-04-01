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
}
