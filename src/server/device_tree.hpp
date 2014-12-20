#ifndef _OUROBOROS_DEVICE_TREE_HPP_
#define _OUROBOROS_DEVICE_TREE_HPP_

#include <data/base.hpp>
#include <data/data_store.hpp>
#include <memory>

namespace ouroboros
{
	/**	Implementation of a singleton class to hold information about the
	 *	data being stored (TODO and custom functionality?).
	 * 
	 */
	template<class field>
	class device_tree
	{
	public:
		/**	Gets the instance of the device_tree. (TODO Should we worry about thread safety?)
		 *
		 *	@returns The instance of the device_tree.
		 */
		static device_tree& get_device_tree();
		
		/**	Gets the data_store object holding all of the data.
		 *
		 *	@returns The data_store object holding all of the data.
		 */
		data_store<field>& get_data_store();
		
	private:
		/**	This class can only be instantiated by itself.
		 * 
		 */
		device_tree();
		static std::unique_ptr<device_tree> mpTree;
		
		std::unique_ptr<data_store<field>> mpDataStore;
	};
	
}

#include "device_tree.ipp"

#endif//_OUROBOROS_DEVICE_TREE_HPP_
