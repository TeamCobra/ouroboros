#ifndef _OUROBOROS_DEVICE_TREE_HPP_
#define _OUROBOROS_DEVICE_TREE_HPP_

#include <ouroboros/data/base.hpp>
#include <ouroboros/data/data_store.hpp>
#include <ouroboros/function_manager.h>

namespace ouroboros
{
	/**	Implementation of a singleton class to hold information about the
	 *	data being stored.
	 *
	 */
	template<class field>
	class device_tree
	{
	public:
		/**	Gets the instance of the device_tree.
		 *
		 *	@returns The instance of the device_tree.
		 */
		static device_tree& get_device_tree();

		/**	Gets the data_store object holding all of the data.
		 *
		 *	@returns The data_store object holding all of the data.
		 */
		data_store<field>& get_data_store();

		/** Returns the function manager associated with the functions in the
		 *		data_store.
		 *
		 *	@returns The function manager associated with the functions in the
		 *		data_store.
		 *
		 */
		function_manager& get_function_manager();

		~device_tree();

	private:
		/**	This class can only be instantiated by itself.
		 *
		 */
		device_tree();
		static device_tree *mpTree;

		data_store<field> *mpDataStore;
		function_manager mFunctionManager;
	};

}

#include "device_tree.ipp"

#endif//_OUROBOROS_DEVICE_TREE_HPP_
