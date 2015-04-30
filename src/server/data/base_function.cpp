#include "base_function.h"
#include <sstream>
#include <limits>

namespace ouroboros
{
	base_function::base_function()
	:var_field("", "")
	{}


	base_function::base_function(
		const std::string& aTitle,
		const std::string& aDescription,
		const std::vector<std::string>& aParameters)
	:var_field(aTitle, aDescription), mParameters(aParameters)
	{}

	std::string base_function::getJSON() const
	{
		std::stringstream ss;
		ss << "{ \"type\" : \"function\", ";
		
		std::string base = var_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);
		ss << "{ \"parameters\" : { ";
		
		typedef std::vector<std::string>::const_iterator iter;
		for (iter itr = mParameters.begin(); itr != mParameters.end(); ++itr)
		{
			ss << *itr << ", ";
		}
		if (!mParameters.empty())
		{
			base.erase(base.find_last_of(','), 1);
		}
		
		ss << "} }";
		
		return ss.str();
	}

	bool base_function::setJSON(const JSON& aJSON)
	{
		base_function backup(*this);
		bool result = true, found = false;
		if (aJSON.exists("title"))
		{
			found = true;
			this->setTitle(aJSON.get("title"));
		}
		if (aJSON.exists("description"))
		{
			found = true;
			this->setDescription(aJSON.get("description"));
		}
		
		if (aJSON.exists("parameters"))
		{
			found = true;
			std::string params = aJSON.get("parameters");
		}

		if(!result)
		{
			*this = backup;
		}
		return result && found;
	}
}
