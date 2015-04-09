#include "base_boolean.h"
#include <sstream>
#include <limits>

namespace ouroboros
{
	base_boolean::base_boolean()
	:var_field("", ""), mValue(false)
	{}
	
	
	base_boolean::base_boolean(
		const std::string& aTitle,
		const std::string& aDescription,
		bool aValue)
	:var_field(aTitle, aDescription), mValue(aValue)
	{}
	
	
	void base_boolean::setValue(bool aNum)
	{
		mValue = aNum;
	}
	
	std::string base_boolean::getJSON() const
	{
		std::stringstream ss;
		ss << "{ \"type\" : \"boolean\", ";
		
		std::string base = var_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);
		
		ss << base << ", \"value\" : " << std::boolalpha << mValue;
		ss << " }";
		
		return ss.str();;
	}
	
	
	bool base_boolean::setJSON(const JSON& aJSON)
	{
		base_boolean backup(*this);
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

		std::stringstream ss;
		if (aJSON.exists("value"))
		{
			bool num;
			found = true;

			ss << aJSON.get("value");
			ss >> num;

			if (ss)
			{
				setValue(num);
			}
			else
			{
				result = false;
			}
		}

		if(!result)
		{
			*this = backup;
		}
		return result && found;
	}
}
