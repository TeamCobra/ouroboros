#include <data/base.hpp>
#include <data/data_store.hpp>
#include <memory>

namespace ouroboros
{
	template <class field>
	device_tree<field>& device_tree<field>::get_device_tree()
	{
		if (!mpTree)
		{
			mpTree.reset(new device_tree<field>());
			
		}
		return *mpTree;
	}
	
	template <class field>
	device_tree<field>::device_tree()
	{
		//Load data store here TODO
		group<var_field> result("root", "Root node");
		result.add(new base_string("main", "This is the main text.", "", "", 10, 10, 10));
		
		mpDataStore.reset(new data_store<field>(std::move(result)));
	}
	
	template <class field>
	data_store<field>& device_tree<field>::get_data_store()
	{
		return *mpDataStore;
	}
	
	template<class field>
	std::unique_ptr<device_tree<field>> device_tree<field>::mpTree;
}