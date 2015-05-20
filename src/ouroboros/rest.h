#ifndef _OUROBOROS_REST_H_
#define _OUROBOROS_REST_H_

#include <mongoose/mongoose.h>

#include <utility>
#include <string>


namespace ouroboros
{
	/**	Checks whether the given C string represents a REST URI. The REST URIs
	 *	recognize must be one of the following:
	 *
	 *			/group/(group-names)/name/(itemName)
	 *			/group/(group-names)
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
		GROUPS, FIELDS, CALLBACK, FUNCTIONS, NONE
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
		/**	Constructor
		 *
		 *	@param [in] apConn Pointer to a connection object supplied by the
		 *		Mongoose server.
		 *	@param [in] aUri URI received from the server.
		 *
		 */
		rest_request(mg_connection *apConn, const std::string& aUri);

		/**	Destructor.
		 *
		 */
		~rest_request();

		/**	Returns the type of HTTP request for the connection of this request.
		 *
		 * 	@returns The HTTP request type for the connection of this request.
		 */
		http_request_type getHttpRequestType() const;

		/**	Returns the type of REST request type for the given URI.
		 *
		 * 	@returns The HTTP request type for the given URI.
		 */
		rest_request_type getRestRequestType() const;

		/**	Returns the field the REST request targets, if any.
		 *
		 *	@returns The field the REST request targets, or empty if none.
		 */
		std::string getFields() const;

		/**	Returns the function the REST request targets, if any.
		 *
		 *	@returns The function the REST request targets, or empty if none.
		 */
		std::string getFunctions() const;

		/**	Returns the group the REST request targets, if any.
		 *
		 *	@returns the group the REST request targets, or empty if none.
		 */
		std::string getGroups() const;

		/**	Returns a pointer to the connection object associated with the
		 *		request.
		 *
		 *	@returns A pointer to the connection object associated with the
		 *		request.
		 */
		mg_connection *getConnection() const;

	private:
		http_request_type mHttpType;
		rest_request_type mRestType;
		std::string mGroups;
		std::string mFields;
		std::string mFunctions;

		mg_connection *mpConnection;
	};
}

#endif//_OUROBOROS_REST_H_
