#include <server/device_tree.hpp>

namespace ouroboros
{
	namespace detail
	{
		/**	Builds the data tree used by the main data_store instance.
		 *	TODO Function to be templated by code generator.
		 * 
		 */
		template<class field>
		group<field> build_tree();
	}
}