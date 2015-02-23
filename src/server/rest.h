#ifndef _OUROBOROS_REST_H_
#define _OUROBOROS_REST_H_

#include <utility>
#include <string>
#include <mongoose/mongoose.h>

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
	enum rest_request_type
	{
		GROUPS, FIELDS, CUSTOM, NONE
	};

	/**	Represents the HTTP request type received.
	 * 
	 */
	enum http_request_type
	{
		POST, GET, DELETE, PUT, UNKNOWN
	};

	class rest_request
	{
	public:
		rest_request(mg_connection *apConn, const std::string& aUri);
		~rest_request();
		http_request_type getHttpRequestType() const;
		rest_request_type getRestRequestType() const;
		
		std::string getFields() const;
		std::string getGroups() const;
		//std::string getCustom();
		
		mg_connection *getConnection() const;
		
	private:
		http_request_type mHttpType;
		rest_request_type mRestType;
		std::string mGroups;
		std::string mFields;
		
		mg_connection *mpConnection;
		//TODO custom
	};
}

#endif//_OUROBOROS_REST_H_
