#include <sstream>
#include <limits>
#include <map>
#include "base_enum.h"

namespace ouroboros
{
	base_enum::base_enum()
	:var_field("", ""), mValue(0)
	{}
	
	base_enum::base_enum(
		const std::string& aTitle,
		const std::string& aDescription,
		int aValue,
		const std::map<std::string, int>& aEnums)
	:var_field(aTitle, aDescription), mValue(aValue), mEnumMap(aEnums)
	{
		std::map<std::string, int>::iterator itr = mEnumMap.begin();
		for (; itr != mEnumMap.end(); ++itr)
		{
			mValueMap[itr->second] = itr->first;
		}
		
		if (!checkValidity(aValue))
		{
			mValue = 0;
			throw(std::out_of_range("Given enum is out of range!"));
		}
		
	}
	
	base_enum::base_enum(
		const std::string& aTitle,
		const std::string& aDescription,
		const std::string& aValue,
		const std::map<std::string, int>& aEnums)
	:var_field(aTitle, aDescription), mEnumMap(aEnums)
	{
		std::map<std::string, int>::iterator itr = mEnumMap.begin();
		for (; itr != mEnumMap.end(); ++itr)
		{
			mValueMap[itr->second] = itr->first;
		}
		
		if (checkValidity(aValue))
		{
			mValue = mEnumMap[aValue];
		}
		else
		{
			mValue = 0;
			throw(std::out_of_range("Given enum is out of range!"));
		}
		
	}
	
	bool base_enum::setValue(const std::string& aEnum)
	{
		if (checkValidity(aEnum))
		{
			mValue = mEnumMap[aEnum];
			return true;
		}
		return false;
	}
	
	bool base_enum::setValue(int aEnum)
	{
		if (checkValidity(aEnum))
		{
			mValue = aEnum;
			return true;
		}
		return false;
	}
	
	std::string base_enum::getJSON() const
	{
		std::stringstream ss;
		ss << "{ \"type\" : \"base_enum\", ";
		
		std::string base = var_field::getJSON();
		base.erase(base.find_first_of('{'), 1);
		base.erase(base.find_last_of('}'), 1);
		
		ss << base << ", \"value\" : " << mValueMap[mValue] << ", ";
		ss << "enums : [ ";
		
		std::map<std::string, int>::iterator itr = mEnumMap.begin();
		for (; itr != mEnumMap.end(); ++itr)
		{
			ss << itr->first << ", ";
		}
		base.erase(base.find_last_of(", "), 1);
		ss << " ]";
		ss << " }";
		
		return ss.str();;
	}
	
	bool base_enum::setJSON(const JSON& aJSON)
	{
		base_enum backup(*this);
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
			long num;
			std::string value;
			found = true;

			ss << aJSON.get("value");
			ss >> value;
			char * ptr = reinterpret_cast<char*>(1); // Make it not null on purpose, strtol should set it to null on success
			num = strtol(value.c_str(), &ptr, 10);
			if (!ptr)
			{
				result = setValue(num);
			}
			else
			{
				result = setValue(value);
			}

			if (!ss || !result)
			{
				result = false;
			}

			ss.clear();
			ss.str("");
		}

		if(!result)
		{
			*this = backup;
		}
		return result && found;

	}

	bool base_enum::checkValidity (int aEnum) const
	{
		if (mValueMap.count(aEnum))
		{
			return true;
		}
		return false;
	}
	
	bool base_enum::checkValidity (const std::string& aEnum) const
	{
		if (mEnumMap.count(aEnum))
		{
			return true;
		}
		return false;
	}
}
