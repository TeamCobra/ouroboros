#include <ouroboros/data/misc.h>

#include <string>
#include <vector>
#include <cctype>
#include <clocale>
#include <algorithm>

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

		std::string normalize_name(const std::string& aField)
		{
			//Create a new string for lookup purposes with all lower case letters and no spaces
			std::string result(aField);
			std::transform(result.begin(), result.end(), result.begin(), (int(*)(int))std::tolower);
			std::replace(result.begin(), result.end(), ' ', '_');
			return result;
		}
	}
}
