#include <data/base.hpp>
#include <data/data_store.hpp>

namespace ouroboros
{
	group<var_field> get_device_group()
	{
		group<var_field> result("root", "Root node");
		result.add(new base_string("main", "This is the main text.", "", "", 10, 10, 10));
		return result;
	}

	data_store<var_field> get_data_store()
	{
		data_store<var_field> result(get_device_group());
		return result;
	}
}