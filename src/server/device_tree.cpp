#include <server/device_tree.tpp>

namespace ouroboros
{
	namespace detail
	{
		template<>
		group<var_field> build_tree()
		{
			group<var_field> result("root", "Root node");
			result.add(new base_string("main", "This is the main text.", "", "", 10, 10, 10));
			return result;
		}
	}
}