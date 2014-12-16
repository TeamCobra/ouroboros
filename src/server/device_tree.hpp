#ifndef _OUROBOROS_DEVICE_TREE_HPP_
#define _OUROBOROS_DEVICE_TREE_HPP_

#include <data/base.hpp>
#include <data/data_store.hpp>
#include <memory>

namespace ouroboros
{
	template<class field>
	class device_tree
	{
	public:
		static device_tree& get_device_tree();
		group<field> get_device_group();
		data_store<field>& get_data_store();
		
	private:
		device_tree();
		static std::unique_ptr<device_tree> mpTree;
		
		std::unique_ptr<data_store<field>> mpDataStore;
	};
	
}

#include "device_tree.ipp"

#endif//_OUROBOROS_DEVICE_TREE_HPP_