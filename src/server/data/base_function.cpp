#include "base_function.h"
#include <sstream>
#include <limits>

namespace ouroboros
{
	base_function::base_function(
		const std::string& aTitle,
		const std::string& aDescription,
		const std::vector<std::string>& aParameters,
		function_manager &aManager)
	:var_field(aTitle, aDescription), mParameters(aParameters), mpManager(&aManager)
	{}

	std::string base_function::getJSON() const
	{
		std::stringstream ss;
		std::string tmp;
		
		ss << "{ \"type\" : \"function\", ";
		
		tmp = var_field::getJSON();
		tmp.erase(tmp.find_first_of('{'), 1);
		tmp.erase(tmp.find_last_of('}'), 1);
		ss << tmp;
		ss << ", { \"parameters\" : { ";
		
		typedef std::vector<std::string>::const_iterator iter;
		for (iter itr = mParameters.begin(); itr != mParameters.end(); ++itr)
		{
			ss << "\"" << *itr << "\" ,";
		}
		tmp = ss.str();
		
		if (!mParameters.empty())
		{
			tmp.erase(tmp.find_last_of(','), 1);
		}
		
		tmp += "} }";
		
		return tmp;
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
		
		//This executes the function
		if (aJSON.exists("parameters"))
		{
			found = true;
			//Make sens of params. It should be a JSON hash, from
			//string -> string, where key is the param name, and value is the
			//string representation of the value
			std::string params = aJSON.get("parameters");
			JSON jparams(params);
			typedef std::vector<std::string>::const_iterator iter;
			std::vector<std::string> parameters;
			for (iter itr = mParameters.begin(); itr != mParameters.end(); ++itr)
			{
				if (jparams.exists(*itr))
				{
					parameters.push_back(jparams.get(*itr));
				}
				else
				{
					result = false;
					break;
				}
			}
			
			if (result)
			{
				//Call function
				mpManager->execute_function(this->getTitle(), parameters);
			}
		}

		if(!result)
		{
			*this = backup;
		}
		return result && found;
	}
}
