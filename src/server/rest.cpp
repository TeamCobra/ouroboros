#include "slre.h"
#include <string.h>
#include <stdbool.h>
#include "rest.h"
#include <string>
#include <utility>

namespace ouroboros
{
	static const char * full_regex = "^/group/([^/]+)/name/([^/]+)$";
	static const char * group_regex = "^/group/([^/]+)$";

	bool is_REST_URI(const char* aURI)
	{
		int result = slre_match(full_regex, aURI, strlen(aURI), NULL, 0, 0);
		int group_result = slre_match(group_regex, aURI, strlen(aURI), NULL, 0, 0);
		return (result >= 0 || group_result >= 0);
	}

	std::pair<std::string, std::string> extract_group_name(const char* aURI)
	{
		struct slre_cap match[2];
		//FIXME should we limit the size?
		slre_match(full_regex, aURI, strlen(aURI), match, 2, 0);
		std::pair<std::string, std::string> result;
		result.first.assign(match[0].ptr, match[0].len);
		result.first.assign(match[1].ptr, match[1].len);
		return result;
	}

	std::string extract_group(const char* aURI)
	{
		struct slre_cap match[1];
	    //FIXME should we limit the size?
	    slre_match(group_regex, aURI, strlen(aURI), match, 1, 0);
	    std::string result;
		result.assign(match[0].ptr, match[0].len);
		return result;
	}
}
