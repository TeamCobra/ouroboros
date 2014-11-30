#include "faux_dstore.hpp"
#include <vector>

namespace ouroboros
{
		
		base_field *faux_dstore::get(const std::string& aName, const std::string& aGroup)
		{
			return new LED();
		}
		
		std::vector<base_field *> get(const std::string& aGroup)
		{
			std::vector <base_field*> result;
			for (std::size_t i = 0; i < 10; ++i)
			{
				result.push_back(new LED());
			}
			return result;
		}
}