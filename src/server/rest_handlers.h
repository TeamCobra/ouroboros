#ifndef _OUROBOROS_REST_HANDLERS_H_
#define _OUROBOROS_REST_HANDLERS_H_

#include <string>
#include <mongoose/mongoose.h>

namespace ouroboros
{
	/**	Function to handle a REST call having a group and a name specified.
	 *
	 *	@param conn Pointer to the connection structure returned by Mongoose.
	 *	@param aURI URI containing the REST call.
	 */
	void handle_name_REST(struct mg_connection *conn, const std::string& aURI);

	/**	Function to handle a REST call having only a group specified.
	 *
	 *	@param conn Pointer to the connection structure returned by Mongoose.
	 *	@param aURI URI containing the REST call.
	 */
	void handle_group_REST(struct mg_connection *conn, const std::string& aURI);

	/**	Function to handle a REST call having a custom call specified.
	 *
	 *	@param conn Pointer to the connection structure returned by Mongoose.
	 *	@param aURI URI containing the REST call.
	 */
	void handle_custom_REST(struct mg_connection *conn, const std::string& aURI);
}
#endif//_OUROBOROS_REST_HANDLERS_H_