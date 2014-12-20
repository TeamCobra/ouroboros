#include "misc.h"
#include <string>
#include <vector>

namespace ouroboros
{
	namespace detail
	{
		std::vector<std::string> split(const std::string& aString, const std::string& aDelim)
		{
			std::string tmp(aString);
			std::vector<std::string> result;
			std::size_t end = std::string::npos;
			while ((end = tmp.find(aDelim)) != std::string::npos)
			{
				result.push_back(tmp.substr(0, end));
				tmp = tmp.substr(end + aDelim.length(), std::string::npos);
				end = std::string::npos;
			}
			result.push_back(tmp);
			
			return result;
		}
	}
}
