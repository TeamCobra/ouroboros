#ifndef _OUROBOROS_DEVICE_TREE_H_
#define _OUROBOROS_DEVICE_TREE_H_

#include <data/base.hpp>
#include <data/data_store.hpp>

namespace ouroboros
{
	group<var_field> get_device_group();

	data_store<var_field> get_data_store();
}

#endif//_OUROBOROS_DEVICE_TREE_H_