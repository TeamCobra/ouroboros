#ifndef _OUROBOROS_REST_HANDLERS_H_
#define _OUROBOROS_REST_HANDLERS_H_

#include <string>

namespace ouroboros
{
	void handle_name_REST(const std::string& aURI);

	void handle_group_REST(const std::string& aURI);

	void handle_custom_REST(const std::string& aURI);
}
#endif//_OUROBOROS_REST_HANDLERS_H_