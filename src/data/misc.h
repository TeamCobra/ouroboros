#ifndef _OUROBOROS_MISC_H_
#define _OUROBOROS_MISC_H_

#include <vector>
#include <string>

namespace ouroboros
{
	namespace detail
	{
		std::vector<std::string> split(const std::string& aString, const std::string& aDelim);
	}
}

#endif//_OUROBOROS_MISC_H_
