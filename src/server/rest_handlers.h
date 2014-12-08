#ifndef _OUROBOROS_REST_HANDLERS_H_
#define _OUROBOROS_REST_HANDLERS_H_

#include <string>
#include <mongoose/mongoose.h>

namespace ouroboros
{
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI);

	void handle_group_REST(struct mg_connection *conn, const std::string& aURI);

	void handle_custom_REST(struct mg_connection *conn, const std::string& aURI);
}
#endif//_OUROBOROS_REST_HANDLERS_H_