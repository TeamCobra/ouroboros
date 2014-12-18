#include "JSON.h"
#include <string>

namespace ouroboros
{
	JSON::JSON()
	:mpArr(nullptr)
	{}
	
	JSON::JSON(const std::string& aJSON)
	:mpArr(parse_json2(aJSON.c_str(), aJSON.length()))
	{}
	
	JSON::~JSON()
	{
		free(mpArr);
	}
	
	bool JSON::exists(const std::string& aPath) const
	{
		if (mpArr)
		{
			const json_token * ptr = find_json_token(mpArr, aPath.c_str());
			if (ptr)
			{
				return true;
			}
		}
		return false;
	}
	
	std::string JSON::get(const std::string& aPath) const
	{
		if (mpArr)
		{
			const json_token * ptr = find_json_token(mpArr, aPath.c_str());
			if (ptr)
			{
				return std::string(ptr->ptr, ptr->len);
			}
		}
		return std::string();
	}
	
	bool JSON::empty() const
	{
		return (!mpArr);
	}
	
}