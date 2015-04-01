#ifndef _OUROBOROS_CALLBACK_H_
#define _OUROBOROS_CALLBACK_H_

#include <string>

namespace ouroboros
{
	template <typename Item, typename Func>
	class callback
	{
	public:
		
		/**	Constructor.
		 *
		 *	@param [in] aGroup Group to listen to for changes.
		 *	@param [in] aFunc Functor to register for the callback. The functor
		 *		must behave as a void(std::string, std::string) functions,
		 *		where the first parameter is the group and the second parameter
		 *		the field that is being observed.
		 */
		callback(const Item& aItem, Func aFunc);
		
		/**	Function called by others as a callback.
		 *
		 */
		void operator()() const;
		
	private:
		Item mItem;
		Func mFunc;
	};
	
	template <typename Item, typename Func, typename Cond>
	class conditional_callback
	{
	public:
		
		/**	Constructor.
		 *
		 *	@param [in] aGroup Group to listen to for changes.
		 *	@param [in] aFunc Functor to register for the callback. The functor
		 *		must behave as a void(std::string, std::string) functions,
		 *		where the first parameter is the group and the second parameter
		 *		the field that is being observed.
		 *	@param [in] aCond Functor that evaluates to true when the callback
		 *		should be triggered, and false otherwise. The functor must
		 *		behave as a bool(const Item&) function, where Item is the type
		 *		of the object being compared.
		 */
		conditional_callback(const Item& aItem, Func aFunc, Cond aCond);
		
		/**	Function called by others as a callback.
		 *
		 */
		void operator()() const;
		
	private:
		Item mItem;
		Func mFunc;
		Cond mCond;
	};
	
	template <typename Item, typename Cond>
	class conditional
	{
	public:
		conditional(Cond aConditional);
		bool operator()(const Item& aItem) const;
	private:
	};
}

#include "callback.ipp"

#endif//_OUROBOROS_CALLBACK_H_

