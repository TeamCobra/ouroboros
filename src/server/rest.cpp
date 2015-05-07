#include "slre.h"
#include <string.h>
#include <stdbool.h>
#include "rest.h"
#include <string>
#include <utility>

namespace ouroboros
{
	static const std::string character_set("[a-z0-9-_\\.]");
	static const std::string full_regex("^/groups/(" + character_set + "+)/fields/(" + character_set + "+)/?$");
	static const std::string group_regex("^/groups/(" + character_set + "+)/?$");
	static const std::string root_field_regex("^/fields/(" + character_set + "+)/?$");
	static const std::string root_group_regex("^/groups/?$");
	static const std::string full_regex_callback("^/groups/(" + character_set + "+)/fields/(" + character_set + "+)/callback?$");
	static const std::string root_field_regex_callback("^/fields/(" + character_set + "+)/callback?$");
	
	/**	Extracts the group from the given REST URI.
	 * 
	 *	@param [in] aURI URI containing a REST group.
	 *
	 *	@returns String representation of the groups found in the URI,
	 *		'-' delimited.
	 */
	static std::string extract_group(const std::string& aURI);

	/**	Extracts the group and item name from the given REST URI.
	 * 
	 *	@param [in] aURI URI containing a REST group and name.
	 *
	 *	@returns Pair containing a string representation of the groups found in
	 *		the URI (first), '-' delimited, and the string representation of the
	 *		name of the item (second).
	 */
	static std::pair<std::string, std::string> extract_group_name(
		const std::string& aURI);
	
	bool is_REST_URI(const std::string& aURI)
	{
		int result =
			slre_match(full_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int group_result =
			slre_match(group_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_field_result =
			slre_match(root_field_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_group_result =
			slre_match(root_group_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_callback_result = 
			slre_match(root_field_regex_callback.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int field_callback_result = 
			slre_match(full_regex_callback.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
			
		return (result >= 0 || group_result >= 0
			       || root_field_result >= 0 || root_group_result >= 0 || root_callback_result >= 0 || field_callback_result >= 0);
	}

	static rest_request_type get_rest_request_type(const std::string& aURI)
	{
		int item_result = slre_match(
			full_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_item_result = slre_match(
			root_field_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		if (item_result >= 0 || root_item_result >= 0)
			return FIELDS;
		
		int group_result = slre_match(
			group_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_group_result = slre_match(
			root_group_regex.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		if (group_result >= 0 || root_group_result >= 0)
			return GROUPS;
		
		int item_callback_result = slre_match(
			full_regex_callback.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		int root_item_callback_result = slre_match(
			root_field_regex_callback.c_str(), aURI.c_str(), aURI.length(), NULL, 0, 0);
		if (item_callback_result >= 0 || root_item_callback_result >= 0)
			return CALLBACK;
		
		return NONE;
	}

	static http_request_type get_http_request_type(const std::string& aMethodType)
	{
		if (aMethodType == "PUT")
		{
			return PUT;
		}
		else if (aMethodType == "POST")
		{
			return POST;
		}
		else if (aMethodType == "GET")
		{
			return GET;
		}
		else if (aMethodType == "DELETE")
		{
			return DELETE;
		}
		return UNKNOWN;
	}

	std::pair<std::string, std::string> extract_group_name(const std::string& aURI)
	{
		std::pair<std::string, std::string> result;

		//Check if user is accessing field in root first
		struct slre_cap match[1];
		if(slre_match(root_field_regex.c_str(), aURI.c_str(), aURI.length(), match, 1, 0) >= 0)
		{
			result.first = std::string();
			result.second.assign(match[0].ptr, match[0].len);
		}
		else
		{
			struct slre_cap match[2];
			if (slre_match(full_regex.c_str(), aURI.c_str(), aURI.length(), match, 1, 0) >= 0)
			{
				slre_match(full_regex.c_str(), aURI.c_str(), aURI.length(), match, 2, 0);
			}
			else
			{
				slre_match(full_regex_callback.c_str(), aURI.c_str(), aURI.length(), match, 2, 0);
			}

			//Copy group title from match to remove remaining characters
			std::string groupTitle(match[0].ptr);
			groupTitle.erase(groupTitle.begin()+match[0].len, groupTitle.end());
			
			result.first.assign(groupTitle);
			result.second.assign(match[1].ptr, match[1].len);
		}

		return result;
	}

	std::string extract_group(const std::string& aURI)
	{
		struct slre_cap match[1];
		std::string result;
		if(slre_match(group_regex.c_str(), aURI.c_str(), aURI.length(), match, 1, 0) >= 0)
		{
			result.assign(match[0].ptr, match[0].len);	
		}

		return result;
	}
	
	rest_request::rest_request(mg_connection* apConnection, const std::string& aUri)
	:mHttpType(get_http_request_type(apConnection->request_method)),
		mRestType(get_rest_request_type(aUri)), mpConnection(apConnection)
	{
		switch (mRestType)
		{
			case FIELDS:
			case CALLBACKS:
			{
				std::pair<std::string, std::string> data = extract_group_name(aUri);
				mGroups = data.first;
				mFields = data.second;
			}
				break;
				
			case GROUPS:
				mGroups = extract_group(aUri);
				break;
				
			case NONE:
				break;
		}
	}
	
	rest_request::~rest_request()
	{}
	
	http_request_type rest_request::getHttpRequestType() const
	{
		return mHttpType;
	}
	
	rest_request_type rest_request::getRestRequestType() const
	{
		return mRestType;
	}
	
	std::string rest_request::getFields() const
	{
		return mFields;
	}
	
	std::string rest_request::getGroups() const
	{
		return mGroups;
	}
	
	mg_connection *rest_request::getConnection() const
	{
		return mpConnection;
	}
}
