#ifndef _OUROBOROS_CALLBACK_H_
#define _OUROBOROS_CALLBACK_H_

#include <string>

namespace ouroboros
{
	template <typename Func>
	class callback
	{
	public:
		//FIXME move implementation to callback.ipp
		
		/**	Constructor.
		 *
		 *	@param [in] aGroup Group to listen to for changes.
		 *	@param [in] aFunc Functor to register for the callback. The functor
		 *		must behave as a void(std::string, std::string) functions,
		 *		where the first parameter is the group and the second parameter
		 *		the field that is being observed.
		 */
		callback(const std::string& aGroup, Func aFunc)
		:mFunc(aFunc), mGroup(aGroup)
		{}
		
		/**	Constructor
		 *
		 *	@param [in] aGroup Group to listen to for changes.
		 *	@param [in] aField Field to listen to for changes.
		 *	@param [in] aFunc Functor to register for the callback. The functor
		 *		must behave as a void(std::string, std::string) functions,
		 *		where the first parameter is the group and the second parameter
		 *		the field that is being observed.
		 */
		callback(const std::string& aGroup, const std::string& aField, Func aFunc)
		:mFunc(aFunc), mGroup(aGroup), mField(aField)
		{}
		
		/**	Function called by others as a callback.
		 *
		 */
		void operator()() const
		{
			mFunc(mGroup, mField);
		}
		
	private:
		Func mFunc;
		std::string mGroup;
		std::string mField;
	};
}

#endif//_OUROBOROS_CALLBACK_H_