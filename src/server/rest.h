#ifndef _OUROBOROS_REST_H_
#define _OUROBOROS_REST_H_

#include <utility>
#include <string>

namespace ouroboros
{
	/**	Checks whether the given C string represents a REST URI. The REST URIs
	 *	recognize must be one of the following:
	 * /group/(group-names)/name/(itemName)
	 * /group/(group-names)
	 * 
	 *	@param aURI C string URI to check.
	 * 
	 *	@returns True if the given C string represents a REST URI,
	 *		false otherwise.
	 */
	bool is_REST_URI(const std::string& aURI);

	/**	Represents the type of REST call received.
	 * 
	 */
	enum REST_call_type
	{
		GROUP, NAME, CUSTOM, NONE
	};

	/**	Represents the HTTP request type received.
	 * 
	 */
	enum HTTP_request_type
	{
		POST, GET, DELETE, PUT, UNKNOWN
	};

	/**	Checks the given URI and determines the type of REST call that it needs.
	 * 
	 *	@param [in] aURI String to check for the type of REST call needed to handle
	 *		the pattern matched.
	 *
	 *	@returns An enum describing the type of REST call needed to handle the
	 *		URI.
	 */
	REST_call_type get_REST_call_type(const std::string& aURI);
	
	/**	Converts a string representation of the HTTP request type to an enum.
	 * 
	 *	@param [in] aHTTP_Type String representation of the HTTP request type.
	 *
	 *	@returns An enum describing the type of HTTP request type received.
	 *
	 */
	HTTP_request_type get_HTTP_request_type(const std::string& aHTTP_Type);

	/**	Extracts the group from the given REST URI.
	 * 
	 *	@param [in] aURI URI containing a REST group.
	 *
	 *	@returns String representation of the groups found in the URI,
	 *		'-' delimited.
	 */
	std::string extract_group(const std::string& aURI);

	/**	Extracts the group and item name from the given REST URI.
	 * 
	 *	@param [in] aURI URI containing a REST group and name.
	 *
	 *	@returns Pair containing a string representation of the groups found in
	 *		the URI (first), '-' delimited, and the string representation of the
	 *		name of the item (second).
	 */
	std::pair<std::string, std::string> extract_group_name(
		const std::string& aURI);
}

#endif//_OUROBOROS_REST_H_
