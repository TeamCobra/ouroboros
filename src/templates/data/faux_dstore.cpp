#include "faux_dstore.hpp"
#include <vector>

namespace ouroboros
{

	static std::vector<LED> leds({0,1,2,3,4,5,6,7,8,9});

	
	var_field *faux_dstore::get(const std::string& aName, const std::string& aGroup)
	{
		return &leds[4];
	}
	
	std::vector<var_field *> faux_dstore::get(const std::string& aGroup)
	{
		std::vector <var_field*> result;
		for (std::size_t i = 0; i < 3; ++i)
		{
			result.push_back(&leds[i]);
		}
		return result;
	}
	
	std::string LED::getValue() const
	{
		return std::string("{ \"title\" : \"" + this->getTitle() + "\", "
			+ " \"description\" : \"" + this->getDescription() + "\", " + " }");
	}
}