#ifndef _OUROBOROS_CALLBACK_H_
#define _OUROBOROS_CALLBACK_H_

#include <string>

namespace ouroboros
{
	template <typename Func>
	class callback
	{
	public:
		callback(const std::string& aGroup, Func aFunc)
		:mFunc(aFunc), mGroup(aGroup)
		{}
		
		callback(const std::string& aGroup, const std::string& aField, Func aFunc)
		:mFunc(aFunc), mGroup(aGroup), mField(aField)
		{}
		
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