#include "misc.h"
#include <string>
#include <vector>

namespace ouroboros
{
	namespace detail
	{
		std::vector<std::string> split(const std::string& aString, const std::string& aDelim)
		{
			//FIXME this returns empty strings if there are consecutive delims
			std::vector<std::string> result;
			std::size_t end = std::string::npos, start = 0;
			while ((end = aString.substr(start, end).find(aDelim)) != std::string::npos)
			{
				result.push_back(aString.substr(start, end));
				start = end + aDelim.length();
			}
			result.push_back(aString.substr(start, end));
			
			return result;
		}
	}
}
