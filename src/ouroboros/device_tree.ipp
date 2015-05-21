#include <ouroboros/data/base.hpp>
#include <ouroboros/data/data_store.hpp>
#include <ouroboros/device_tree.tpp>

namespace ouroboros
{
	template <class field>
	device_tree<field>& device_tree<field>::get_device_tree()
	{
		if (!mpTree)
		{
			mpTree = new device_tree<field>();
		}
		return *mpTree;
	}

	template <class field>
	device_tree<field>::device_tree()
	{
		mpDataStore =
			new data_store<field>(
				detail::build_tree<field>(mFunctionManager));
	}

	template <class field>
	device_tree<field>::~device_tree()
	{
		//we need to free all of the resources we've allocated
		delete mpDataStore;
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

	template<class field>
	device_tree<field> *device_tree<field>::mpTree;
}
