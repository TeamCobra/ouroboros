#include <server/device_tree.tpp>
#include <data/base.hpp>
#include <string>

namespace ouroboros
{
	namespace detail
	{
		template<>
		group<var_field> build_tree()
		{
			group<var_field> result("root", "Root node");
			group<var_field> *g1 = new group<var_field>("g1", "");
			group<var_field> *g2 = new group<var_field>("g2", "");
			
			result.add(new base_string("main", "This is the main text.", "", "", 10, std::pair<std::size_t, std::size_t>(10, 10)));
			result.add(g1);
			g1->add(g2);
			g2->add(new base_string("i1", "!!!", "", "", 10, std::pair<std::size_t, std::size_t>(10, 10)));
			
			result.add(new group<var_field>("g3", ""));
			return result;
		}
	}
}