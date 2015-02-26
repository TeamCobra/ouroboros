#include <string>

namespace ouroboros
{
	template <typename Func>
	callback<Func>::callback(const std::string& aGroup, Func aFunc)
	:mFunc(aFunc), mGroup(aGroup)
	{}
	
	template <typename Func>
	callback<Func>::callback(
		const std::string& aGroup, const std::string& aField, Func aFunc)
	:mFunc(aFunc), mGroup(aGroup), mField(aField)
	{}
		
	template <typename Func>
	void callback<Func>::operator()() const
	{
		mFunc(mGroup, mField);
	}
}
