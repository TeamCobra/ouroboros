#ifndef _OUROBOROS_FAUX_DSTORE_HPP_
#define _OUROBOROS_FAUX_DSTORE_HPP_

#include "base.hpp"
#include <vector>

namespace ouroboros
{
	class LED : public var_field
	{
	public:
		LED()
		:var_field("LED","This is a fake LED")
		{}
		
		std::string getValue() const override;
	private:
		
	};
	
	class faux_dstore
	{
	public:
		base_field *get(const std::string& aName, const std::string& aGroup);
		std::vector<base_field *> get(const std::string& aGroup);
	};
}

#endif//_OUROBOROS_FAUX_DSTORE_HPP_
