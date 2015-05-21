#include <ouroboros/device_tree.hpp>

namespace ouroboros
{
	namespace detail
	{
		/**	Builds the data tree used by the main data_store instance.
		 *	NOTE: This function is to be templated by code generator.
		 *
		 */
		template<class field>
		group<field> build_tree(function_manager& aFunctionManager);
	}
}
