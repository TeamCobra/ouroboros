#ifndef _OUROBOROS_REST_H_
#define _OUROBOROS_REST_H_

#include <utility>
#include <string>

namespace ouroboros
{
	bool is_REST_URI(const char* aURI);

	enum class REST_call_type {
		GROUP, NAME, CUSTOM, NONE
	};

	REST_call_type get_REST_call_type(const std::string& aURI);

	std::string extract_group(const char* aURI);

	//pair.first is group, pair.second is name
	std::pair<std::string, std::string> extract_group_name(const char* aURI);
}

#endif//_OUROBOROS_REST_H_
