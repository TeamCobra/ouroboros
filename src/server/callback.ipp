#include <string>

namespace ouroboros
{
	template <typename Item, typename Func>
	callback<Item, Func>::callback(const Item& aItem, Func aFunc)
	:mItem(aItem), mFunc(aFunc)
	{}
		
	template <typename Item, typename Func>
	void callback<Item, Func>::operator()() const
	{
		mFunc(mItem);
	}
	
	template <typename Item, typename Func, typename Cond>
	conditional_callback<Item, Func, Cond>::conditional_callback(const Item& aItem, Func aFunc, Cond aCond)
	:mItem(aItem), mFunc(aFunc), mCond(aCond)
	{}
	
	template <typename Item, typename Func, typename Cond>
	void conditional_callback<Item, Func, Cond>::operator()() const
	{
		if (mCond(mItem))
		{
			mFunc(mItem);
		}
	}
}
