#include <ouroboros/data/base.hpp>
#include <ouroboros/data/data_store.hpp>
#include <ouroboros/device_tree.tpp>

namespace ouroboros
{
	template <class field>
	device_tree<field>::device_tree()
	:mRootGroup(detail::build_tree<field>(mFunctionManager))
	{
		mpDataStore = new data_store<field>(mRootGroup);
	}

	template <class field>
	device_tree<field>::~device_tree()
	{
		//we need to free all of the resources we've allocated
		delete mpDataStore;
		detail::free_tree(mRootGroup);
	}

	template <class field>
	data_store<field>& device_tree<field>::get_data_store()
	{
		return *mpDataStore;
	}
	
	template <class field>
	function_manager& device_tree<field>::get_function_manager()
	{
		return mFunctionManager;
	}
}
