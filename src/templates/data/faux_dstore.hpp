#ifndef _OUROBOROS_FAUX_DSTORE_HPP_
#define _OUROBOROS_FAUX_DSTORE_HPP_

#include "base.hpp"
#include <vector>

namespace ouroboros
{
	class LED : public var_field
	{
	public:
		LED(int aNum)
		:var_field("LED","This is a fake LED"), mNum(aNum)
		{}
		
		std::string getValue() const override;
	private:
		int mNum;
	};
	
	class faux_dstore
	{
	public:
		var_field *get(const std::string& aName, const std::string& aGroup);
		std::vector<var_field *> get(const std::string& aGroup);
	};
}

#endif//_OUROBOROS_FAUX_DSTORE_HPP_
